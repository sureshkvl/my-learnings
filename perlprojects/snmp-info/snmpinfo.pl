use SNMP::Info;
my $info = new SNMP::Info(                             
 	                        AutoSpecify => 1,
                            Debug       => 0,
                            # The rest is passed to SNMP::Session
                            DestHost    => '192.168.101.1',
                            Community   => 'public',
                            Version     => 2
                          ) or die "Can't connect to device.\n";

my $err = $info->error();
die "SNMP Community or Version probably wrong connecting to device. $err\n" if defined $err;

#Global Scalar methods RFC
$name  = $info->name();
$uptime = $info->uptime();
$contact = $info->contact();
$location = $info->location();
$layers = $info->layers();
$no_of_ports = $info->ports();
$ipfwding = $info->ipforwarding();
printf "sysName (%s) \nsysUpTime  (%s) \nsysContact (%s) \nsysLocation (%s)\n",$name,$uptime,$contact,$location;
printf "sysServices (%s)\n",$layers;
printf "no-of-ports (%d) \nip-forwarding-enabled (%d)\n",$no_of_ports,$ipfwding;

#object scalar methods
printf "DeviceType (%s) \nSNMP Community (%s) \nSNMP Version (%d)\n",$info->device_type(), $info->snmp_comm(), $info->snmp_ver();

#intefaces - returns hash
$ifs = $info->interfaces();
$ifdesc = $info->i_description();  
$iftype = $info->i_type();
$ifspeed = $info->i_speed();
$ifnames = $info->i_name();
$ifmacs = $info->i_mac();

print "interfaces \n";
print "Port\t Name \t Description\t Type \t Speed \t macaddress\n";
foreach my $iid (keys %$ifs)
{
	printf "(%d)\t (%s)\t (%s)\t (%s)\t (%d)\t (%s) \n",$ifs->{$iid},$ifnames->{$iid},$ifdesc->{$iid},$iftype->{$iid},$ifspeed->{$iid},$ifmacs->{$iid} ;
}


#IP Address Tables
$ipindexs = $info->ip_index(); 
$ipaddrs =  $info->ip_table();
$ipmasks = $info->ip_netmask();
printf " index \t address \t mask \n";
foreach my $id (keys %$ipindexs)
{
    printf "(%d)\t (%s) \t (%s) \n", $ipindexs->{$id},$ipaddrs->{$id},$ipmasks->{$id} ;
}

#IP Routing Tables
$iproutes = $info->ipr_route();
$ipifs = $info->ipr_if();
$ipdests = $info->ipr_dest();
$iptypes = $info->ipr_type();
$ipprotos = $info->ipr_proto();
$iprmasks = $info->ipr_mask();
printf "Route \t Interface \t Destination \t Type \t Protocol \t Mask \n";
foreach my $id (keys %$iproutes)
{
    printf "(%s) \t (%d) \t (%s) \t (%d) \t (%d) \t (%s)\n",$iproutes->{$id}, $ipifs->{$id},$ipdests->{$id},$iptypes->{$id},$ipprotos->{$id},$iprmasks->{$id};
 
}
