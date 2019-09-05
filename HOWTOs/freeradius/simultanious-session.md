FreeRadius:


There are two scenarios will come on authentication.

A. Authenticate only one connection for a user (No simultanious logins)


  Eg:  VPN user is getting authenticated and start using the service from DEVICEA....
  It possible that, he can use a same credentials on DEVICEB and authenicates and use it at the same time.. (simultaneously).

  This can be avoided by freeradius  "Simultaneous-Use" AVP.


  configuration:

  1. update the mysql radcheck table with "Simultaneous-Use" AV.

  Login in to mysql with radius user..
  
  mysql> INSERT INTO radcheck (username, attribute, op, value) VALUES ('suresh', 'Simultaneous-Use', ':=', 1);

  mysql> select * from radcheck;
+----+----------+------------------+----+-------------+
| id | username | attribute        | op | value       |
+----+----------+------------------+----+-------------+
|  1 | test     | Password         | == | test        |
|  2 | suresh   | Password         | == | suresh      ||
|  6 | suresh   | Simultaneous-Use | := | 1           |
+----+----------+------------------+----+-------------+
4 rows in set (0.00 sec)

mysql> 

2. enable the "simul_count_query"   in the  /etc/freeradius/sql/mysql/dialup.conf.
By default it is disabled. please uncomment it.


3. in the /etc/freeradius/radiusd.conf , enable sql
	$INCLUDE sql.conf
	$INCLUDE sql/mysql/counter.conf

4. Enable sql in the /etc/freeradius/site-enabled/default

	authorize , accounting,session, post-auth  --- section

5. 4. Enable sql in the /etc/freeradius/site-enabled/inner-tunnel
	same as 4. but only few sections

thats all.

testing:
  1. connect the "Test" user on first time and starts the accounting... eitther radclient, or openvpn.
  2. connect the same "Test" user on second time (simulataneously)... this should be rejected.

  Eg:
  root@8a2f053f89d3:/etc/freeradius# radtest suresh suresh localhost 100 testing123
Sending Access-Request of id 128 to 127.0.0.1 port 1812
	User-Name = "suresh"
	User-Password = "suresh"
	NAS-IP-Address = 10.1.0.3
	NAS-Port = 100
	Message-Authenticator = 0x00000000000000000000000000000000
rad_recv: Access-Reject packet from host 127.0.0.1 port 1812, id=128, length=68
	Reply-Message = "\r\nYou are already logged in - access denied\r\n\n"


--------------------------------------------


B.  Configure the user with Expiry date, if the Date is expired Reject the user.

	"Expiration" AV is used for user expiry check.

	1. Login to mysql
	2. update the mysql radcheck table with "Expiration" AV.

    INSERT INTO radcheck (username, attribute, op, value) VALUES ('suresh', 'Expiration', ':=', '26 JUN 2015');

    thanks all.

	Refer :  cat /usr/share/doc/freeradius/rlm_expiration





  Ref:
  http://lists.freeradius.org/pipermail/freeradius-users/2011-November/057043.html
  FreeRadius Beginners Guide by packetpub.
    