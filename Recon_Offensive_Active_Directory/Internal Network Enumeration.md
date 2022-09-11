
### Basic COmmand
```
systeminfo | findstr /B /C:"Domain"
wmic computersystem get domain
Get-ChildItem C:\Users
Get-LocalGroupMember Administrators | ft Name, PrincipalSource

```



### Create A list of IP Address
```
python -c 'for i in range(1,254): print "192.168.1.%d" % i' > Target.txt
```
### Identifying Live Network 

```
nmap -sn -v -oG nmapped.txt 192.168.1.1-254
grep Up nmapped.txt | cut -d" " -f2 > targets.txt
nmap -n -A -oA portscan_result_tcp -Pn -vvvv -iL targets.txt
grep -i 192.168.3.100 portscan_result_tcp_full.gnmap
```

### ARP Scan
```
arp-scan 192.168.200.0/24 | tee arp_scan_3_0.txt
cat arp_scan* | grep -i "vmware" | cut -d$'\t' -f1 > ip_list #To get a clean list of hosts


for /l %i in (1,1,254) do ping -n 1 -w 100 192.168.1.%i >> results.txt
Get-Content .\results.txt | Select-String -Pattern "Received = 1" -Context 1,0
```
# Ping sweep

### Powershell Ip Scan
```
1..254 | ForEach-Object {Get-WmiObject Win32_PingStatus -Filter "Address='192.168.1.$_' and Timeout=200 and ResolveAddressNames='true' and StatusCode=0" | select ProtocolAddress*}
```

### Linux
```
for i in `seq 1 255`; do ping -c 1 192.168.1.$i | tr \\n ' ' | awk '/1 received/ {print $2}'; done > ip.txt
```
### Window
```
for /L %i in (1,1,255) do @ping -n 1 -w 200 192.168.1.%i > nul && echo 192.168.1.%i is up

```
### Identifying domains/workgroups and domain membership within the target network
```
nbtscan 192.168.100.0/24
nbtstat -A 192.168.100.10
```

### IPV4 Service Enumeration
```
nmap -Pn -n --open -p500  192.168.0.0/24 
nmap -Pn -n --open -p161  192.168.0.0/24 
nmap -p445 --script smb-vuln-ms17-010 x.x.x.0/24
nmap -sV --script=realvnc-auth-bypass x.x.x.0/24
nmap --script http-webdav-scan -p80,8080 x.x.x.0/24
nmap -p80 --script http-default-account x.x.x.0/24
nmap -Pn -n --open -p6000-6005 --script=x11-access 172.31.6.0/24  
nmap -Pn -n --open -p3389 --script=rdp-vuln-ms12-020,rdp-enum-encryption 172.31.6.0/24 
nmap -sT -PN -n -sV -p 21,22,23,25,80,110,139,443,445,1433,1521,3306,3389,8080,10000 192.168.2.9/24 
nmap -sT -PN -n -sV -p 21,22,23,25,80,110,139,443,445,1433,1521,3306,3389,8080,10000 192.168.2.9/24 | awk '/22\/open/ {print $2}' 
```
### IPV6 Service Enumeration
```
ping6 -c4 -I eth0 ff02::1 | tee ipv6
cat ipv6 | cut -d" " -f4 | sort -u | grep fe | sed s'/:$//' | tee ipv6_list
nmap -6 -T4 -Pn -open -sSVC -A –p0-65535 -iL ipv6_list 
```




