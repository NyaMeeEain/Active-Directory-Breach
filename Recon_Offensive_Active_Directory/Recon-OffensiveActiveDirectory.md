### User Enumerations
```
powershell Get-DomainUser | select userprincipalname,userprincipalname,homedirectory,serviceprincipalname
powershell Get-DomainUser | Format-Table name, samaccountname, userprincipalname, description
powershell Get-DomainUser -Credential $Cred | Format-Table name, samaccountname, userprincipalname, description
powershell Get-DomainUser -Filter "(samaccountname=*_adm)" | Select-Object name, samaccountname
powershell Get-DomainUser -Filter "(samaccountname=John*)" | Select-Object name, samaccountname
powershell Get-DomainUser -Identity John
powershell Get-DomainUser -Identity John | select msexchhomeservername,userprincipalname,primarygroupid,homedrive,homedirectory | fl
```
### DomainComputer Enumerations
```
powershell Get-DomainComputer -Properties DnsHostName | Sort-Object -Property DnsHostName
powershell Get-DomainComputer | select cn,objectsid,dnshostname
PowerShell Find-DomainUserLocation | Select-Object UserName, SessionFromName # Identify Each user Sesson On Network
PowerShell Get-DomainComputer -Properties DnsHostName | Sort-Object -Property DnsHostName
powershell Get-NetComputer -OperatingSystem "*Server 2016*" | select operatingsystem,lastlogon,dnshostname
powershell Get-NetComputer | Get-NetLoggedOn | Where {$_.wkui1_username -like "John"} | Select-Object ComputerName
```
### Group Enumerations
```
powershell Get-NetLocalGroup | Select-Object GroupName
Get-NetGroup -domain internal.msp.local -Credential $credential | select samaccountname
powershell Get-NetLocalGroupMember -GroupName Administrators | Select-Object MemberName, IsGroup, IsDomain
powershell Get-NetLoggedOn
```
### Domain Group Members Enumeration
```
To enumerate members of the Domain Admins group
powershell Get-DomainGPO -Properties DisplayName | Sort-Object -Property DisplayName
powershell Get-DomainGroup *admin* -Properties samaccountname | Get-DomainGroupMember  | select -ExpandProperty GroupName
powershell Get-DomainGroupMember "Domain Admins"
powershell Get-DomainGroupMember  "Enterprise Admins"
powershell Get-DomainGroupMember "Enterprise Admins" –Domain acmebank.local
powershell Get-DomainGroup *admin* -Properties samaccountname | Get-DomainGroupMember
```
### DomainGPO Enumeration
```
powershell Get-DomainGPOLocalGroup | select GroupName,GPODisplayName,GPOType,GPOName
powershell Get-DomainOU -GPLink '{A572138C-69A5-4A6B-8210-FE08E6B0282D}' | % {Get-DomainComputer -SearchBase $_.distinguishedname -Properties dnshostname}
powershell Get-DomainOU -GPLink '{66465373-16CB-4F96-BD3A-12AE7D2C2371}' | % {Get-DomainComputer -SearchBase $_.distinguishedname -Properties dnshostname}
powershell Get-DomainOU -GPLink '{8D791281-636D-400A-B495-C9B32753F717}' | % {Get-DomainComputer -SearchBase $_.distinguishedname -Properties dnshostname}
powershell Get-DomainGPO -ComputerIdentity John_PC -Properties DisplayName | Sort-Object -Property DisplayName
```
### Discretionary Access Control Enumeration
Enumerating Discretionary Access Control is very interesting, You compromised accounts or you compromised computer might belong to high privileged groups,which allow Unprivileged User to elevate their privileged depending on which group belong to.

```
get-adgroup -filter * -Credential $credential  -Server iprod.nsomnia.io | sort name | select Name #AD module
Invoke-ACLScanner | Format-Table ObjectDN,AceQualifier,IdentityReferenceName,ActiveDirectoryRights
Get-NetGroup -domain iprod.insomnia.io | select samaccountname
Get-NetGroup *ForestManagers* 
Get-NetGroup organizationadmins | Format-Table displayname,samaccountname,member
Get-DomainGroupMember -domain iprod.nsomnia.io -Credential $credential -Identity "internaladmins" | Select-Object MemberDistinguishedName
Get-ObjectAcl -Domain iprod.nsomnia.io -Credential $credential -SamAccountName ForestManagers 

Get-ObjectAcl -DistinguishedName "ForestManagers" -Domain iprod.nsomnia.io -Credential $credential | Format-Table
Get-ObjectAcl -DistinguishedName "internaladmins" -Domain iprod.nsomnia.io -Credential $credential | Format-Table
Get-DomainUser orgadmin | Format-Table samaccountname,memberof
Get-ObjectAcl -Domain iprod.nsomnia.io -SamAccountName organizationadmins 
Get-ObjectAcl -Domain iprod.nsomnia.io -SamAccountName organizationadmins | Format-Table ObjectDN,ActiveDirectoryRights
Get-ObjectAcl -SamAccountName organizationadmins
```


### Domain Administator Members Groups
```
powershell Get-DomainGroup *admin* -Properties samaccountname | Get-DomainGroupMember | select MemberDomain,GroupName,MemberName
powershell Get-DomainGroupMember -identity *admin* -recurse | select -exp membername
powershell Get-DomainGroup *admin* -Properties samaccountname | Get-DomainGroupMember | select MemberDomain,GroupName,MemberName | fl
```
### Organization Units Enumerations
```
 powershell Get-DomainOU -Properties Name | Sort-Object -Property Name
 
```
# Unconstrained Delegation
```
powershell Get-DomainComputer -Unconstrained | select -exp dnshostname
powershell Get-DomainComputer -Unconstrained | select samaccountname,dnshostname,operatingsystem,useraccountcontrol
powershell Get-DomainComputer -Unconstrained | select samaccountname,dnshostname,useraccountcontrol,dnshostname,operatingsystem
powershell Get-DomainGPOLocalGroup
powershell Get-DomainGPOLocalGroup | select GroupName,GPODisplayName,GPOType,GPOName
powershell Get-DomainOU -GPLink '{A572138C-69A5-4A6B-8210-FE08E6B0282D}' | % {Get-DomainComputer -SearchBase $_.distinguishedname -Properties dnshostname}
powershell Get-DomainOU -GPLink '{66465373-16CB-4F96-BD3A-12AE7D2C2371}' | % {Get-DomainComputer -SearchBase $_.distinguishedname -Properties dnshostname}
powershell Get-DomainOU -GPLink '{8D791281-636D-400A-B495-C9B32753F717}' | % {Get-DomainComputer -SearchBase $_.distinguishedname -Properties dnshostname}

```
### Constrained Delegation
```
Get-NetUser -TrustedToAuth
powershell Get-DomainComputer -TrustedToAuth | select -exp dnshostname 
powerpick Get-DomainComputer -TrustedToAuth | select name,msds-allowedtodelegateto,useraccountcontrol
powershell Get-DomainComputer -TrustedToAuth -Properties distinguishedname,msds-allowedtodelegateto,useraccountcontrol -Verbose | fl 
powershell Get-DomainComputer John_PC.insomnia.io | select -exp msds-AllowedToDelegateTo #To find what services it could delegate for
powershell Get-NetComputer John_PC | select name, msds-allowedtodelegateto, useraccountcontrol | fl
powershell Get-NetComputer John_PC | Select-Object -ExpandProperty msds-allowedtodelegateto | fl
```

### Resource-based constrained delegation
**to check whether you have compromised Machine has GenericWrite permissions over any computer**
```

Get-DomainObjectAcl "dc=it,dc=gcb,dc=local" -ResolveGUIDs | ? { ($_.ObjectType -match 'replication-get') -or ($_.ActiveDirectoryRights -match 'GenericAll')
GET-DomainComputer -Identity John-PC | Where-Object {$_."msds-allowedtoactonbehalfofotheridentity" -ne $null} 
Get-ADComputer -Properties PrincipalsAllowedToDelegateToAccount

```


### DomainPolicy
```
Get-Domain | Select-Object -Expand name
Get-DomainPolicy  -Domain acmebank.local
powershell Get-DomainPolicy -Source DC -Domain acmebank.local
```
### Trust Domain Enumeration


```
#Get a list of all Domain Trusts for the current Domain
powershell Get-NetDomainTrust
powershell Get-NetDomainTrust -Domain <domain>

#Get details about the current Forest
powershell Get-NetForest
powershell powershell Get-NetForest -Forest  acmebank.local

#Get all Domains in the current Forest
powershell Get-NetForestDomain
powershell Get-NetForestDomain -Forest acmebank.local
```
### LAPS Enumerations
```
powershell Get-DomainGPO -Identity "*LAPS*"
powershell-import C:\Users\Commando\Desktop\Weapon\LAPSToolkit.ps1
powershell Get-LAPSComputers 
powershell Find-LAPSDelegatedGroups
powershell Get-Command *AdmPwd*
powershell Get-AdmPwdPassword -ComputerName XXXX


```

