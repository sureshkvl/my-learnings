openvpn-config-examples
=======================

Openvpn configuration examples

contents
----
1. Site to Site VPN Setup with preshared secret key 
2. Site to Site VPN Setup with preshared secret key + multiple keys
3. Site to Site VPN Setup with preshared secret key  + multiple keys + routes
4. Site to Site VPN Setup with preshared secret key  + multiple keys + routes + more secure options
5. Site to Site VPN with certificates
6. Simple Server/clients with certificates 
7. Server/clients with client specific configuration 

10. 3 way routing with static key 




1.Site to Site VPN Setup with preshared secret key
------

a. Generate the secret key.

```
   openvpn --genkey --secret static.key
```
b. copy the secret key to the server pc and client pc (Eg location : /etc/static.key).
 
c. create a server config in the server machine. (Eg:  /etc/server.conf)
   ```
dev tun				               # 
ifconfig 10.10.10.1 10.10.10.2     # tunnel endpoint ips 
secret /etc/static.key             # shared secret key
verb 6					           # log level is 6 - debug
log /var/log/openvpn-server.log	   # log file name
status /var/log/openvpn-server.status	   # log the server status 

```
d. create a client config in the client machine. (Eg:  /etc/client.conf)
```
remote 192.168.122.162			# server IP 
dev tun					        # tun driver
ifconfig 10.10.10.2 10.10.10.1	# tunnel endpoint ips
secret /etc/static.key	        # secret key
log /var/log/openvpn-client.log	# log file name
status /var/log/openvpn-client.status	   # client status log
```
c. run the server and client.
   In the server machine, start  the server
   ```
   openvpn /home/router/server.conf &
   ````
   In the client machine start the client
   ```
   openvpn  /home/router/client.conf &
   ```
e. Verification
- ifconfig will show new tunnel interface and ip.
- check the log files and status file 
- ping the tunnel endpoint.


2. Site to Site VPN Setup with preshared secret key (multiple keys)
----
This example uses the

In this example, openvpn uses 4 keys for communication. refer below.

secret /etc/static.key	  <direction>      # secret key
direction should be 0 or 1.

The following text is taken from the "man openssl"
```
direction parameter enables the use  of  4  distinct  keys  (HMAC-send,  cipher-encrypt,  HMAC-receive,  cipher-decrypt), so that each data flow direction has a different set of HMAC and cipher keys.  This has a number of desirable security properties including eliminating certain kinds of DoS and message replay attacks.
The direction parameter should always be complementary on either side of the connection, i.e. one side should use "0" and the other should use "1", or both sides should omit it altogether. The direction parameter requires that file contains a 2048 bit key.
```

a. create a server config in the server machine. (Eg:  /etc/server.conf)
 ```
dev tun				               # 
ifconfig 10.10.10.1 10.10.10.2     # tunnel endpoint ips 
secret /etc/static.key 1            # shared secret key with directon
verb 6					           # log level is 6 - debug
log /var/log/openvpn-server.log	   # log file name
status /var/log/openvpn-server.status	   # log the server status 

```

b. create a client config in the client machine. (Eg:  /etc/client.conf)
```
remote 192.168.122.162			# server IP 
dev tun					        # tun driver
ifconfig 10.10.10.2 10.10.10.1	# tunnel endpoint ips
secret /etc/static.key 0        # secret key
log /var/log/openvpn-client.log	# log file name
status /var/log/openvpn-client.status	   # client status log
```
c. run the server and client.
   In the server machine, start  the server
   ```
   openvpn /home/router/server.conf &
   ```
   In the client machine start the client
   ```
   openvpn  /home/router/client.conf &
   ```
d. Verification
- ifconfig will show new tunnel interface and ip.
- check the log files and status file 
- ping the tunnel endpoint.





3. Site to Site VPN Setup with preshared secret key  + multiple keys + routes
----

Using the above 1,2 configuration in the below example,

LAN ----- R1 ---- INTERNET------R2----LAN

openvpn site to site VPN is established between R1 & R2. R1 tunnel is able to ping R2 tunnel.
But  R1 - LAN is not reachable by R2- LAN and vice versa.

The problem is routing table doesnt have the update of R2 LAN and R1 LAN.

The manual route update using linux command,   on R2  , pointing the R1-LAN to R2 tunnel interface and vice versa solve the problem.

Also, openvpn supports "route" config , which updates the route.

Eg: 
LAN-R1 : 10.10.10.0/27 
LAN-R2 : 10.10.10.32/27
R1-WAN : 172.16.1.1
R2-WAN : 172.16.1.2

R1: openvpn client config

```
remote 172.16.1.2			    # server IP 
dev tun					        # tun driver
ifconfig 10.20.10.2 10.20.10.1	# tunnel endpoint ips
secret /etc/static.key 0	      # secret key
route 10.10.10.32 255.255.255.224
log /var/log/openvpn-client.log	# log file name
status /var/log/openvpn-client.status	   # client status log
```
R2: openvpn client config

```
dev tun				        # 
ifconfig 10.20.10.1 10.20.10.2   # This is the tunnel endpoints
secret /root/static.key  1        # shared secret key
route 10.10.10.0 255.255.255.224
verb 6					# log level is 6 - debug
log /var/log/openvpn-server.log		# log file name
status /var/log/openvpn-server.status	#  current server status will be stored here
```

4. Site to Site VPN Setup with preshared secret key  + multiple keys + routes + more secure options
---

This example is addon on top of item3. 
Just adding few openvpn config options to make it more secure and consistent.


persist-tun
persist-key

persists the key and tunnel interface.  It make sure the vpn tunnel comes up automatically (actually not shutting down the tunnel and key data) when the openvpn reloads/network issues/ SIGHUP signals etc.

user nobody
group nobody

runs the openvpn with user "nobody" and group "nobody".  Its useful to control the openvpn process by anyuser.

ping n
   -Ping  remote  over  the  TCP/UDP  control channel if no packets have been sent for at least n seconds. no echo mechanism.


ping-restart n
    Similar  to  --ping-exit, but tri
    gger a SIGUSR1 restart after n seconds pass without reception of a ping or other packet from remote. It try to re-estibalish with client/server.


keep-alive n m
    combination ping + ping restart.
    ping every n seconds
    m is interval for ping-restart




proto p
     Use protocol p for communicating with remote host.  p can be udp, tcp-client, or tcp-server.  Default is udp.

local host
    Local  host name or IP address for bind.  If specified, OpenVPN will bind to this address only.  If unspecified, OpenVPN will  bind to all interfaces.


remote host [port] [proto]
    Remote host name or IP address.  If --remote is unspecified, OpenVPN will listen for packets from any IP address, but will not act  on  those  packets  unless  they  pass  all authentication tests.

lport port
    TCP/UDP port number for bind.

rport port
   TCP/UDP port number for remote.


client.conf

```
proto udp
remote 172.16.1.2			# server IP 
lport 10000
rport 10000
local 172.16.1.1
dev tun					        # tun driver
ifconfig 10.20.10.2 10.20.10.1	# tunnel endpoint ips
secret /etc/static.key 0	        # secret key
route 10.10.10.32 255.255.255.224
log /var/log/openvpn-client.log	# log file name
status /var/log/openvpn-client.status	   # client status log
keepalive 10 60
persist-tun
persist-key
```

server.conf

```
proto udp
local 172.16.1.2
remote 172.16.1.1
lport 10000
rport 10000
keepalive 10 60
persist-tun
persist-key
dev tun				        # 
ifconfig 10.20.10.1 10.20.10.2   # This is the tunnel endpoints
secret /root/static.key  1        # shared secret key
route 10.10.10.0 255.255.255.224
verb 6					# log level is 6 - debug
log /var/log/openvpn-server.log		# log file name
status /var/log/openvpn-server.status	#  current server status will be stored here

```


5. Site to Site VPN with certificates
--------

server.conf
```
server 192.168.1.0 255.255.255.248
proto udp
lport 10000
rport 10000
dev tun					       
ca /home/ubuntu/ca.crt
cert /home/ubuntu/server.crt
key /home/ubuntu/server.key
dh  /home/ubuntu/dh1024.pem
log /var/log/openvpn-server.log	
status /var/log/openvpn-server.status	   
keepalive 10 60
persist-tun
persist-key

```

client.conf
```
client
proto udp
lport 10000
rport 10000
remote 172.16.1.1
dev tun					       
ca /home/ubuntu/ca.crt
cert /home/ubuntu/client1.crt
key /home/ubuntu/client1.key
ifconfig 10.20.10.2 10.20.10.1
log /var/log/openvpn-client.log	
status /var/log/openvpn-client.status	   
keepalive 10 60
persist-tun
persist-key

```



6. Simple Server/clients with certificates 
----

For generating the certs please refer 
http://openvpn.net/index.php/open-source/documentation/howto.html#pki
Inbuilt openvpn cert generation tools.


Topology :

server --- client1
       ---- client2
       ---- client3

configuration

server.conf
```
proto udp
port 12000
dev tun
server 192.168.1.0 255.255.255.0
ca /home/ubuntu/ca.crt
cert /home/ubuntu/server.crt
key /home/ubuntu/server.key
dh  /home/ubuntu/dh1024.pem
log /var/log/openvpn-server.log	
status /var/log/openvpn-server.status	
keepalive 10 60
persist-tun
persist-key
```

client1.conf

```
client
remote 172.16.1.1
proto udp
port 12000
dev tun
ca /home/ubuntu/ca.crt
cert /home/ubuntu/client1.crt
key /home/ubuntu/client1.key
log /var/log/openvpn-client.log	
status /var/log/openvpn-client.status	   
keepalive 10 60
persist-tun
persist-key


```
client2.conf

```
client
remote 172.16.1.5
proto udp
port 12000
dev tun
ca /home/ubuntu/ca.crt
cert /home/ubuntu/client2.crt
key /home/ubuntu/client2.key
log /var/log/openvpn-client.log	
status /var/log/openvpn-client.status	   
keepalive 10 60
persist-tun
persist-key

```

7. Setting up the internet sharing  (private/secure intenet )

a.

In the openvpn server configuration, include the 
        push "redirect-gateway def1"
        push "dhcp-option DNS 10.8.0.1"


server.conf
```
proto udp
port 12000
dev tun
server 192.168.1.0 255.255.255.0
ca /etc/certs/ca.crt
cert /etc/certs/server.crt
key /etc/certs/server.key
dh  /etc/certs/dh2048.pem
log /var/log/openvpn-server.log
status /var/log/openvpn-server.status
route-gateway 192.168.1.1
push "dhcp-option 8.8.8.8"
push "redirect-gateway def1"
push "route-delay 5"
keepalive 10 60
persist-tun
persist-key


```

b. enable ip forward in the openvpn server machine

sudo sysctl -w net.ipv4.ip_forward=1

Reference  :  
http://askubuntu.com/questions/311053/how-to-make-ip-forwarding-permanent

c.  configure the Firewall (iptables) to forward the traffic to internet

    iptables -t nat -A POSTROUTING -s <tunnel subnet> -o <out interface> -j MASQUERADE

    Ex:

    iptables -t nat -A POSTROUTING -s 10.8.0.0/24 -o eth0 -j MASQUERADE

Ref: https://openvpn.net/index.php/open-source/documentation/howto.html#pki



8.configure without certs (client side - only username, password authentication)

include this below line in the server conf
	client-cert-not-required

the complete server.conf is below
```
proto udp
port 12000
dev tun
server 192.168.241.0 255.255.255.0
ca /etc/certs/ca.crt
cert /etc/certs/server.crt
key /etc/certs/server.key
dh  /etc/certs/dh2048.pem
client-cert-not-required
log /var/log/openvpn-server.log 
status /var/log/openvpn-server.status  
route-gateway 192.168.241.1
push "dhcp-option 8.8.8.8"
push "redirect-gateway def1"
push "route-delay 5"
plugin /etc/openvpn/radiusplugin.so /etc/openvpn/radiusplugin.cnf
keepalive 10 60
persist-tun
persist-key
```

The client side conf is below,

```
client
remote 52.27.225.192 
proto udp
port 12000
dev tun
ca /etc/certs/ca.crt
keepalive 10 60
auth-user-pass
persist-tun
persist-key

```
In the client side, no need  of certs, only "ca.crt" is required... auth-user-pass has been given hence username, password authenitcation happens

Reference :  https://networklessons.com/linux/openvpn-server-usernamepassword-authentication/





