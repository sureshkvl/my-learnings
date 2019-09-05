CoovaChilli setup in VM Environment:
====================================
I wanted to install coovachilli for learning in VM environment..
The below is the write up for that..


Setup Overview:
--------------
			
   Host machine ------VM1---------VM2
 
1) 
   VM1:
   role: coovachilli
   ubuntu 14.04 server software
   Interface:
       - eth0 - kvm(default NAT mode) : IP DHCP, (192.168.122.3)
       - eth1 - bridge (connected to VM2 via bridge - lansw).. No IP assignemnt

   VM2:
   role : client
   ubuntu 14.04 desktop 
   Interface :
       - eth0 -bridge (connected to VM1 via bridge - lansw) .. No IP Assignment.

2)
   In the host machine, create a bridge for lan (lansw bridge).
       sudo brctl addbr lansw
       sudo ifconfig lansw up


VM1(coovachilli machine) Setup:
------------------------------
During the VM creation, Add two network interfaces... one is default NAT(will act as WAN), the another one is Bridge (specify the bridge name as lansw) will act as LAN.

1. install coovachilli

          Reference document:   http://www.radiusdesk.com/getting_started/install_ubuntu_coovachilli

       sudo apt-get install build-essential linux-headers-server libssl-dev
       apt-get update
       sudo apt-get install build-essential linux-headers-server libssl-dev
       sudo apt install devscripts debhelper
	wget http://ap.coova.org/chilli/coova-chilli-1.3.0.tar.gz
        tar xvzf coova-chilli-1.3.0.tar.gz 
	cd coova-chilli-1.3.0/
	debuild -i -us -uc -b
 	cd ..
	sudo dpkg --install coova-chilli_1.3.0_amd64.deb

2. install haserl
download the haserl and install it.
        wget http://sourceforge.net/projects/haserl/?source=typ_redirect
        tar xvzf haserl-*
        cd haserl-0.9.35/
        ./configure
        make
        make install

3. Configuration changes

     a.  vi /etc/default/chilli
	     changes:  START_CHILLI=1


         /etc/init.d/chilli start

         After starting the chlli, tun0 intefface should be enabled..

     b.
           Edit the /etc/chilli/wwwsh file and give the absolute path of haserl as  below

           #haserl=$(which haserl 2>/dev/null)
           haserl=/usr/local/bin/haserl

     c.
          cd /etc/chilli/
          cp defaults config

            Edit config file, and check the LAN & WAN interface names are correctly configured..

            HS_LANIF=eth1
            Note:  I havent changed anything in this file (default configuraion runs fine.).

     d.
         create ipup.sh, and include the below lines.
             iptables -I INPUT -i tun0 -p tcp -m tcp --dport 80 --dst 10.1.0.1 -j ACCEPT
             iptables -I INPUT -i tun0 -p tcp -m tcp --dport 443 --dst 10.1.0.1 -j ACCEPT
             iptables -I INPUT -i tun0 -p tcp -m tcp --dport 22 --dst 10.1.0.1 -j ACCEPT
             iptables -I INPUT -i tun0 -p tcp -m tcp --dport 8000 --dst 10.1.0.1 -j ACCEPT
     e.
         create ipdown.sh, and include the below lines.
                iptables -D INPUT -i tun0 -p tcp -m tcp --dport 80 --dst 10.1.0.1 -j ACCEPT
                iptables -D INPUT -i tun0 -p tcp -m tcp --dport 443 --dst 10.1.0.1 -j ACCEPT
                iptables -D INPUT -i tun0 -p tcp -m tcp --dport 22 --dst 10.1.0.1 -j ACCEPT
                iptables -D INPUT -i tun0 -p tcp -m tcp --dport 8000 --dst 10.1.0.1 -j ACCEPT


       Edit  /etc/init.d/chilli file for enabling NAT..

     f.
            #NAT mod
            iptables -F POSTROUTING -t nat
            iptables -I POSTROUTING -t nat -o $HS_WANIF -j MASQUERADE
            #END NAT mod


4. Restart the chilli

       Stop the chill and start, to take the config effect.

        sudo /etc/init.d/chilli stop
        sudo /etc/init.d/chilli start


5. freeradius setup:
   freeradius  should be installed and user should be added.  

   Refer: openvpn/freeradius_integreation.mD



VM2(client machine) setup:
--------------------------
 only ethernet interface should in DHCP..   coovachilli will serve the IP.
 no other setup required.



End Testing
-------

Once chilli is started, VM2 client machine will get the IP dynamically  .

open the Web browser (firefox) and start the browsing.. 

you will see the redirection page goes to login page and will ask for creds to login.


the creds will be authenticated with  freeradius and start the browsing.


  
         


   






