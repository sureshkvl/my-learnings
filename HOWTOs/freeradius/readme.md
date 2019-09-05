FreeRadius:

1. Installation

In ubuntu,

	apt-get install freeradius  freeradius-mysql  freeradius-common  freeradius-utils

	Note: only required freeradius packages are selected.

config files will be located in /etc/freeradius

/etc/freeradius/radiusd.conf    ----  The master configuration file / entry point. consists 									  general configurations (modules, log, virtual 											  servers,..)

/etc/freeradius/clients.conf    ----  contains the clients (Freeradius client or NAS device) 										details.. such as IP, sharedsecret.

/etc/freeradius/dictionary      ----   main dictonary file.. all AVP names must be defined 										   in the dictionary . All dictionary files are /usr/										   share/freeradius located here.

/etc/freeradius/sql.conf        ----   sql server details (server ip, db, username,pw etc)


/etc/freeradius/users           ----   flat file for storing username/password-authentication


/etc/freeradius/sites-enabled/default ----   Authentication Authorization Accounitng 													configuration details 


/etc/freeradius/sites-enabled/inner-tunnel ---- similar to default file.. serves only radius 											run in TTLS/PEAP 



To start the server
	freeradius 

	-X switch enable debug prints

To Test the server 

	radtest
	radclient






Reference :  FreeRadius Beginners Guide by packetpub.


