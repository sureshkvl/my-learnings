

How to Stop the iptables
=====================

sudo iptables-save > $HOME/firewall.txt
sudo iptables -X
sudo iptables -t nat -F
sudo iptables -t nat -X
sudo iptables -t mangle -F
sudo iptables -t mangle -X
sudo iptables -P INPUT ACCEPT
sudo iptables -P FORWARD ACCEPT
sudo iptables -P OUTPUT ACCEPT


-t : table name (filter,nat,mangle)
-F : Flush the selected chain (all the chains in the table if none is given). This is equivalent to deleting all the rules one by one.
-X : Delete the optional user-defined chain specified. There must be no references to the chain. If there are, you must delete or replace the referring rules before the chain can be deleted.
-P chainNameHere ACCEPT : Set the policy for the chain to the given target.

After the IPTables is disabled/cleaned, the output of iptables -L is below:

sudo iptables -L


Chain INPUT (policy ACCEPT)
target     prot opt source               destination         

Chain FORWARD (policy ACCEPT)
target     prot opt source               destination         

Chain OUTPUT (policy ACCEPT)
target     prot opt source               destination 
