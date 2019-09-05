Setting up the PPTP client in the ubuntu linux.
=====================

Prerequistis: 

  Make sure the PPTP server has been configure properly.

    a.  PPTP clients  IP Address range - should be part of the PPTP Server IP POOL (usuall LAN IP Address range).
    b.  username, password should be configured.



Setup:


1. installation

sudo apt-get install pptp-linux network-manager-pptp


2. configure the username/password  in the /etc/ppp/chap-secrets file
``` 	
vi /etc/ppp/chap-secrets

$ sudo cat /etc/ppp/chap-secrets 
# Secrets for authentication using CHAP
# client	server	secret			IP addresses
test       PPTP              test                  * 
```

Note : Give server as PPTP,  and IP addresses as *

3. create the pptp connection file in /etc/ppp/peers/
 
 vi /etc/ppp/peers/vpnconnection1

 sudo cat /etc/ppp/peers/conn1 
pty "pptp 10.1.5.23 --nolaunchpppd"
name test 
remotename PPTP
require-mppe-128
file /etc/ppp/options.pptp
ipparam conn1

In this,  10.1.5.23 is the PPTP server IP, "test" is the username.  ipparam "conn1" is the connection file(this file) name.


4. Create a Routing Entry file.. (Once tunnel is establish the route entry needs to be added. this route details to be added here)
In our case, we need to mention the route " for PPTP server Lan subnet pointint to PPP0 interface"

$ cat /etc/ppp/ip-up.d/vpn1-route 
route add -net 192.168.1.0/24 dev ppp0


And change it to executable
chmod +x /etc/ppp/ip-up.d/vpn1-route


5. Testing.
pppd call conn1


Logs will be present in the /var/log/messages or /var/log/syslog





Reference Page:


http://websistent.com/how-to-configure-a-linux-pptp-vpn-client/