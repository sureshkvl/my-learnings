Openvpn + Freeradius Integreation
==


Sceanario:
---

OpenVPN Server needs to talk to FreeRadius for authenticating the openvpn clients. Freeradius is a widely used AAA Server.


### 1. Configuring the Openvpn server

1. install the openvpn radius plugin  from this portal http://www.nongnu.org/radiusplugin/
     a. download and install in ubuntu  (ubuntu 14.04)

     	apt-get install libgcrypt-dev
     	wget http://www.nongnu.org/radiusplugin/radiusplugin_v2.1a_beta1.tar.gz
        tar xvzf radiusplugin_v2.1a_beta1.tar.gz 
        cd  radiusplugin_v2.1a_beta1
        make
        cp radiusplugin.so /etc/openvpn/.
        cp radiusplugin.cnf /etc/openvpn/.

     b. configure the openvpn server
        i) edit /etc/openvpn/server.conf file and add the radius plugin details         
        	plugin /etc/openvpn/radiusplugin.so /etc/openvpn/radiusplugin.cnf

        	refer config_examples.md for other server configurations...


        ii) edit /etc/openvpn/radiusplugin.cnf and update the radius server detils
        	server
			{
				acctport=1813
				authport=1812
				name=localhost
				retry=1
				sharedsecret=testing123
			}

			name -  represents the radius server ip/hostname.
			sharedsecret -  this is secret key used by openvpn server and radius server. 					This same secret key must be configured in the radius server 					also.

	c. run the openvpn server.


### 2. FreeRadius installation & Configuration 

	a.  install freeradius, mysql server thru apt-get.

		apt-get install freeradius freeradius-mysql freeradius-utils mysql-server

	b.  set up the mysql server

		 	service mysql start

		create a db

		 	mysql> CREATE DATABASE radius;
			mysql> GRANT ALL PRIVILEGES ON radius.* TO radius@localhost IDENTIFIED BY "rad-password";
			mysql> flush privileges;
			mysql> exit

		setup the radius schema in the mysql db

		 	mysql -uradius -p radius < /etc/freeradius/sql/mysql/schema.sql


		add a user (username :suresh, password: suresh)

			mysql> use radius;
			mysql> INSERT INTO radcheck (UserName, Attribute, Value) VALUES ('suresh', 'Password', 'suresh');

	c.  configure freeradius

		In /etc/freeradius/sql.conf, the following configuration (mysql server , username, password, db name) to be  correct.. other parameters you can configure as you want.

			sql {
				server = "localhost"
				login = "radius"
				password = "rad-password"
				radius_db = "radius"
			}

		In /etc/freeradius/radiusd.conf file, enable(uncomment) this line
			$INCLUDE sql.conf

		In /etc/freeradius/clients.conf, configure the "shared_secret" of your vpn server details

			client VPN_IP {
				secret = testing123
				nastype = other
			}

			The secret must be same as openvpn shared_secret updated in the /etc/openvpn/radiusplugin.cnf file.

		In /etc/freeradius/sites-available/default  file, enable(uncomment) the line containing ‘sql’ under the ‘authorize {}’ section and line  ‘sql’ under the accounting {} section, also uncomment ‘sql’ under session{}.

		In /etc/freeradius/sites-available/inner-tunnel  file,  uncomment the lines containing ‘sql’ under authorize {} and under session {}.


	d. restart the freeradius
		freeradius -X

	c. test the freeradius with radtest

		syntax:
		radtest <username>  <password>  <radius server ip>  <port>   <shared secret>

		#radtest suresh suresh localhost 1812 testing123

		output :
		This should success (rad_recv: Access-Accept packet from host 127.0.0.1 port 1812, id=250, length=20)


### 3. End to End test

	a.  make sure openvpn server is configured in the step1 and running
	b.  make sure freeradius is configured in step2 and running.
	c.  Configure the openvpn client (refer config_examples.md)
		Update the	/etc/openvpn/client.conf with the below command for user authentication,

			auth-user-pass

	d.  execute the client. It will ask for the username and passowrd and connect it to the 	server.

			$ openvpn  /etc/openvpn/client.conf 
				Fri Jun 19 14:17:58 2015 OpenVPN 2.3.2 x86_64-pc-linux-gnu [SSL (OpenSSL)] [LZO] [EPOLL] [PKCS11] [eurephia] [MH] [IPv6] built on Dec  1 2014
				Enter Auth Username:suresh
				Enter Auth Password:




Reference:
http://techlinux.net/2014/01/configuring-openvpn-to-authenticate-with-freeradius-part-1/
http://techlinux.net/2014/01/configuring-openvpn-to-authenticate-with-freeradius-part-2/


http://linuxdrops.com/install-openvpn-with-freeradius-on-centosrhel-5-or-6-part-2/
http://sourceforge.net/projects/daloradius/