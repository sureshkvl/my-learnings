Opendaylight(ODL) setup & demo with mininet - stey by step guide
================================================================

ODL version :  Lithium
mininet version : (git master branch)

Setup : 
------
Host Machine (ODL controller) <--------------------> VM1(Mininet)

##Host Machine :  

  Ubuntu 14.04 Desktop
  ODL Lithium version
  KVM interface IP : 192.168.122.1

##VM1:

  Ubuntu 14.04 Server
  Mininet (git master branch)
  IP: 192.168.122.3


ODL Installation (in Host machine)
---------------------------------

	1. download the odl file from the distribution-karaf-0.3.0-Lithium.tar.gz  from ODL website.
	2. tar xvzf distribution-karaf-0.3.0-Lithium.tar.gz 
	3. cd distribution-karaf-0.3.0-Lithium/
	4. ./bin/karaf

	karaf command prompt will open... now basic features to be installed as below,


   A. Base features... odl-l2switch-switch --L2 switch feature.. remaining feautres ..????

	feature:install odl-base-all odl-aaa-authn odl-nsf-all odl-adsal-northbound  odl-l2switch-switch

	
   B. Enable the DLUX UI
	
	feature:install odl-dlux-core  odl-dlux-node

	After installing the above packege, DLUX UI is accessible.

        http://localhost:8080/index.html   
        username/password - admin

   C.  Install the restconf and api docs feature - Nortbound APIs are accessible via REST API.  

   Note:  There is no Northbound REST API documentation in ODL portal. Available REST APIs can be viewd after installing "odl-mdsal-apidocs"feature 

	feature:install odl-mdsal-apidocs odl-restconf

    REST API docs
    http://localhost:8181/apidoc/explorer/index.html


    Sample REST API requests:
	
	http://localhost:8080/restconf/modules
	http://localhost:8080/restconf/operational/network-topology:network-topology
    http://localhost:8080/restconf/operational/opendaylight-inventory:nodes/

Wireshark installation on Hostmachine:
--------------------

Install the latest stable wireshark from source (which has openflow protocol dissector inbuilt).



Mininet installation (in VM1)
----------------------------
Login to the VM.
 1. git clone https://github.com/mininet/mininet
 2. cd mininet/
 3. ./util/install.sh -a
 4. sudo mn --mac --switch=ovsk,protocols=OpenFlow13 --controller=remote,ip=192.168.122.1,port=6653 --topo=tree,3


Sample REST APIs for the above topology

http://localhost:8080/restconf/operational/network-topology:network-topology/topology/flow:1/

http://localhost:8080/restconf/operational/opendaylight-inventory:nodes/node/openflow:1

http://localhost:8080/restconf/operational/opendaylight-inventory:nodes/node/openflow:1/node-connector/openflow:1:2



Intenrals:


https://github.com/opendaylight/docs/blob/stable/lithium/manuals/user-guide/src/main/asciidoc/bk-user-guide.adoc


