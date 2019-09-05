
variable image_id {
  default = "3dc0ed38-943a-47c9-aa11-acde51bdad3f"
}

variable flavor_id {
  default = "1"
}

variable region {
  default = "lab2"
}

variable private_key {
  default = "mykey"
}

variable key_pair {
  default = "mykey"
}

resource "openstack_compute_keypair_v2" "mykey" {
  name = "mykey"
  public_key = "${file("mykey.pub")}"
}

resource "openstack_compute_servergroup_v2" "server_group" {
  name = "server_group"
  policies = ["anti-affinity"]
  region = "${var.region}"
} 

resource "openstack_compute_secgroup_v2" "secgroup_icmp_ssh" {
  region = "${var.region}"
  name = "secgroup_icmp_ssh"
  description = "secgroup_icmp_ssh"
  rule {
    from_port = 22
    to_port = 22
    ip_protocol = "tcp"
    cidr = "0.0.0.0/0"
    from_group_id = ""
  }
  rule {
    from_port = "-1"
    to_port = "-1"
    ip_protocol = "icmp"
    cidr = "0.0.0.0/0"
    from_group_id = ""
  }
}


resource "openstack_networking_network_v2" "net_admin" {
  name = "net_admin"
  admin_state_up = "true"
  region = "${var.region}"
}

resource "openstack_networking_subnet_v2" "subnet_admin" {
  name = "subnet_admin"
  network_id = "${openstack_networking_network_v2.net_admin.id}"
  cidr = "10.0.1.0/24"
  ip_version = 4
  region = "${var.region}"
}


resource "openstack_networking_port_v2" "vm1_port1" {
  name = "vm1_port1"
  network_id = "${openstack_networking_network_v2.net_admin.id}"
  admin_state_up = "true"
  security_group_ids = ["${openstack_compute_secgroup_v2.secgroup_icmp_ssh.id}"]
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

resource "openstack_compute_instance_v2" "vm1" {
  region = "${var.region}"
  name = "vm1"
  image_id = "${var.image_id}"
  flavor_id = "${var.flavor_id}"
  network { 
    port = "${openstack_networking_port_v2.vm1_port1.id}"
  }
  key_pair = "${var.key_pair}"
  scheduler_hints {
    group = "${openstack_compute_servergroup_v2.server_group.id}"
  }
  user_data = "#!/bin/bash\n\nscreen -d -m ping ${openstack_networking_port_v2.vm2_port1.fixed_ip.0.ip_address}"
}

resource "openstack_networking_port_v2" "vm2_port1" {
  name = "vm2_port1"
  network_id = "${openstack_networking_network_v2.net_admin.id}"
  admin_state_up = "true"
  security_group_ids = ["${openstack_compute_secgroup_v2.secgroup_icmp_ssh.id}"]
  region = "${var.region}"
  fixed_ip {
    subnet_id = "${openstack_networking_subnet_v2.subnet_admin.id}"
  }
}


resource "openstack_compute_instance_v2" "vm2" {
  region = "${var.region}"
  name = "vm2"
  image_id = "${var.image_id}"
  flavor_id = "${var.flavor_id}"
  network { 
    port = "${openstack_networking_port_v2.vm2_port1.id}"
  }
  key_pair = "${var.key_pair}"
  scheduler_hints {
    group = "${openstack_compute_servergroup_v2.server_group.id}"
  }
  user_data = "#!/bin/bash\n\nscreen -d -m ping ${openstack_networking_port_v2.vm1_port1.fixed_ip.0.ip_address}"
}
