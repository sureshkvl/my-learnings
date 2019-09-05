
/* Creating Key Pair */

resource "openstack_compute_keypair_v2" "mykey" {
  name = "mykey"
  public_key = "${file("mykey.pub")}"
}

/* Creating Security Groups */

resource "openstack_networking_secgroup_v2" "mgmt_secgroup" {
  name = "mgmt_secgroup"
  description = "Allow ssh and TCP Port"
  #delete_default_rules = "true"
}

resource "openstack_networking_secgroup_rule_v2" "mgmt_secgroup_rule1" {
  direction = "ingress"
  ethertype = "IPv4"
  protocol = "tcp"
  port_range_min    = 22
  port_range_max    = 22
  security_group_id = "${openstack_networking_secgroup_v2.mgmt_secgroup.id}"
  remote_ip_prefix = "0.0.0.0/0"
}


/* Creating a Network ,Subnet and Port */

resource "openstack_networking_network_v2" "net_admin" {
  name = "net_admin"
  admin_state_up = "true"
  region = "${var.region}"
}

resource "openstack_networking_subnet_v2" "subnet_admin" {
  name = "subnet_admin"
  network_id = "${openstack_networking_network_v2.net_admin.id}"
  cidr = "10.20.10.0/24"
  ip_version = 4
  region = "${var.region}"
}

resource "openstack_networking_port_v2" "vm1_port1" {
  name = "vm1_port1"
  network_id = "${openstack_networking_network_v2.net_admin.id}"
  admin_state_up = "true"
  security_group_ids = ["${openstack_networking_secgroup_v2.mgmt_secgroup.id}"]
  region = "${var.region}"
  fixed_ip {
    subnet_id = "${openstack_networking_subnet_v2.subnet_admin.id}"
  }
}


resource "openstack_networking_floatingip_v2" "vm1_fip" {
  region = "${var.region}"
  pool = "public"
  port_id = "${openstack_networking_port_v2.vm1_port1.id}"
}


/* Create a Server Instance */

resource "openstack_compute_instance_v2" "test_vm1" {
  name = "test_vm1"
  region = "${var.region}"
  image_id = "${var.image_id}"
  flavor_id = "${var.flavor_id}"
  network { 
    port = "${openstack_networking_port_v2.vm1_port1.id}"
  }
  key_pair = "${var.key_pair}"
}



output "lb_vip_ip" {
  value = "${openstack_networking_floatingip_v2.vm1_fip.address}"
}