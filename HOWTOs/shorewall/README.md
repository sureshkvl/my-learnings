
shorewall 
===



1. installation.

 sudo apt-get install shorewall


2. copy the sample config files and place it in /etc/shorewall
 
Note: shorewall example configs comes with universal, one-interface,two-interfaces,three-interfaces ... copy the relavent config files when you setup..

  cd /etc/shorewall
  sudo cp /usr/share/doc/shorewall/examples/one-interface/* .


3.  Configuration:

    a.
	Edit /etc/shorewall/shorewall.conf and verify 'IP_FORWARDING=On'
	Edit /etc/default/shorewall and set 'startup=1

    b. update the /etc/shorewall/interface file based on your requirements.

         #ZONE	INTERFACE	OPTIONS
         net     eth0            dhcp,tcpflags,logmartians,nosmurfs,sourceroute=0

      Note : The above is the default config of one-interface , this is fine for single interface machine.

    c. update the /etc/shorewall/zones file based on your requirements

        #					OPTIONS			OPTIONS
	fw	firewall
	net	ipv4
       

        Here "net" is the eth0 network , fw is the "local machine", no interfaes associated.
	Note : The above is the default config of one-interface , this is fine for single interface machine.

       
    d.  update the /etc/shorewall/policy file based on your requirements 

      ###############################################################################
	#SOURCE		DEST		POLICY		LOG LEVEL	LIMIT:BURST
	$FW		net		ACCEPT
	net		all		DROP		info
	# The FOLLOWING POLICY MUST BE LAST
	all		all		REJECT		info

	This policy file interpretation is below, 
         Allow packets  which are initated from the local machine to net zone. 
         Drop packets which are initiated fom the net zone to local machine
         Reject all other packets

   e. update the /etc/shorewall/rules file based on your requiremtns. (This file specific to address/port opening)
        # Drop packets in the INVALID state
	Invalid(DROP)  net    	        $FW		tcp
	# Drop Ping from the "bad" net zone.. and prevent your log from being flooded..
	Ping(DROP)	net		$FW
	# Permit all ICMP traffic FROM the firewall TO the net zone
	ACCEPT		$FW		net		icmp


      
4. verification

     To verify the config files are correct.

	sudo shorewall check          
 
    To apply the config
	sudo shorewall restart


References:

https://help.ubuntu.com/community/ShorewallBasics
http://www.tecmint.com/shorewall-a-high-level-firewall-for-configuring-linux-servers/
https://users.cs.jmu.edu/aboutams/Public/CS482_Spring2005/Module%204-%20Firewall/Shorewall%20Tutorial.pdf
http://shorewall.net/Install.htm

