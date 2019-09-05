# Simple Terraform stack 
It creates a Ubuntu 14.04 VM with floating IP.

It does the below:

1. Import a Key
2. Create a security group
3. Create a  Private Network, subnet and port
4. Create a floating IP associate with that port
5. Create a VM (with key, in private network)