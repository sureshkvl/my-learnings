OpenVSwitch
===

Introduction:
------------

OpenVswitch is a opensource Openflow capable virtual switch. typically used to interconnect virtual machines.

Features:
------
    1. VLAN tagging with 802.1q trunkning
    2. STP
    3. LACP
    4. Port Mirroring
    5. Flow Export (netflow,sflow,ipfix)
    6. tunneling (GRE, VXLAN, IPSEC)
    7. QoS Control


How to install:
----
    apt-get install openvswitch-switch


How to stop/start:
----
    sudo service openvswitch-switch start

    sudo service openvswitch-switch stop

Log file:
---
    By default, log files are located in /var/log/openvswitch/  folder.


How to increase the log level:
----    

    List the current logging levels
    # ovs-appctl vlog/list

    To set the new level
        
        ovs-appctl vlog/set module[:facility[:level]]

        Module: any valid module name displayed by list option.
        Facility: must be one of the console, syslog, file
        Level: must be one of the emer, err, warn, info, or dbg.

    Ex:
         ovs-appctl vlog/set ANY:file:dbg
         (or)
         ovs-appctl vlog/set  vconn:file:dbg



Config Examples:
------

Create a bridge:

    ovs-vsctl addbr mybridge

Add a port to the bridge

    ovs-vsctl add-port mybridge eth0

Show a bridge details:

    ovs-vsctl show

To make the brige up:

    ifconfig mybridge up













=======================================================


1. mininet
2. openflow sepcifications
3. ovswitch


ovs-ofctl

topology

mn --topo=single,3 --controller=none --mac
dump
net

h3 python -m SimpleHTTPServer 80 &

h3 ping -c 2 h2
pingall

h1 curl h2
h2 curl h1
h3 curl h1



sh ovs-ofctl show s1

sh ovs-ofctl dump-flows s1


sh ovs-ofctl add-flow s1 action=normal

sh ovs-ofctl del-flows s1

Layer1:
-======
manual addition:

sh ovs-ofctl add-flow s1 priority=500,in_port=1,actions=output:2
sh ovs-ofctl add-flow s1 priority=500,in_port=2,actions=output:1


sh ovs-ofctl add-flow s1 action=drop

sh ovs-ofctl del-flows s1 --strict ---delete the wildcard flows

Layer2:
======
sh ovs-ofctl add-flow s1 dl_src=00:00:00:00:00:01,dl_dst=00:00:00:00:00:02,actions=output:2
sh ovs-ofctl add-flow s1 dl_src=00:00:00:00:00:02,dl_dst=00:00:00:00:00:01,actions=output:1
sh ovs-ofctl add-flow s1 dl_type=0x806,nw_proto=1,actions=flood
	

Layer3:
=======

sh ovs-ofctl add-flow s1 priority=500,dl_type=0x800,nw_src=10.0.0.0/24,nw_dst=10.0.0.0/24,actions=normal
sh ovs-ofctl add-flow s1 arp,nw_dest=10.0.0.1,actions=output:1
sh ovs-ofctl add-flow s1 arp,nw_dest=10.0.0.2,actions=output:2
sh ovs-ofctl add-flow s1 arp,nw_dest=10.0.0.3,actions=output:3


Layer4: 
========
sh ovs-ofctl add-flow s1 arp,actions=normal
sh ovs-ofctl add-flow s1 arp,priority=500,dl_type=0x800,nw_proto=6,tp_dst=80,actions=output:3
sh ovs-ofctl add-flow s1 arp,priority=800,ip,nw_src=10.0.0.3,actions=normal






mininet commands:

mininet> 
h1 route add default gw 10.0.0.254 h1-eth0
h1 arp -s 10.0.0.254 00:00:00:00:00:11


h3 ifconfig h3-eth0 30.0.0.3 netmask 255.255.255.0
h3 route add default gw 30.0.0.1 h3-eth0



