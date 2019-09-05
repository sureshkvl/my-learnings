
SoftEther +  FreeRadius Integreation
===

SoftEther :   multi-protocol VPN software.  

FreeRadius:   AAA Server



1. SoftEther VPN Server installation
---

	a. Download the vpn server

   		$cd /usr/src/

   		# download
   		$sudo wget http://www.softether-download.com/files/softether/v4.17-9562-beta-2015.05.30-tree/Linux/SoftEther_VPN_Server/64bit_-_Intel_x64_or_AMD64/softether-vpnserver-v4.17-9562-beta-2015.05.30-linux-x64-64bit.tar.gz

   		#untar it
   		$sudo tar xvfz softether-vpnserver-v4.17-9562-beta-2015.05.30-linux-x64-64bit.tar.gz
   		$cd vpnserver/

   		#install the build tools
   	   	$sudo apt-get install build-essential -y

   	   	#build it
   		$make

   		#move the directory to /usr/local folder   		
   		$sudo mv vpnserver/ /usr/local/

   		#set the file permissions
   		$cd /usr/local/vpnserver   		
   		$sudo chmod 600 *
 		$sudo chmod 700 vpnserver
 		$sudo chmod 700 vpncmd

 	b. Run the vpn server (in sudo)
 		$sudo ./vpnserver  start


 	c. verify the installation 
 		vpncmd is a multipurpose utility. used to configure server and also a standalone tool.

 		Run the vpncmd and check the server health.

 			$sudo ./vpncmd

 			#select option 3 (Tools)

 			VPN Tools>check

 			output : All checks passed. It is most likely that SoftEther VPN Server / Bridge can operate normally on this system.

 	d. Configure the server.
 			Run the vpncmd	
 			$sudo ./vpncmd
 			select option 1 (Server)

 			set a server password
 				ServerPasswordSet  <password>

 			create a HUB
 				HubCreate VPN

 			Use a Hub
 				Hub VPN
 			To Enable SecureNAT
 				SecureNatEnable
 			To create a user
 				UserCreate suresh
 				UserPasswordSet  <password>

 			Enable the openvpn vpn server
 				ServerCertRegenerate [CN]
 				ServerCertGet ~/cert.cer
 				SstpEnable yes
				OpenVpnEnable yes /PORTS:1194
				OpenVpnMakeConfig ~/my_openvpn_config.zip


			Enable L2TP
				IPsecEnable




Reference : 
https://www.digitalocean.com/community/tutorials/how-to-setup-a-multi-protocol-vpn-server-using-softether
https://github.com/SoftEtherVPN/SoftEtherVPN/issues/94
