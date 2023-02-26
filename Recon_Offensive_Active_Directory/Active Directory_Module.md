
### Quick Chek

```
get-adgroup -filter * -Credential $credential  -Server iprod.nsomnia.io | sort name | select Name
Get-AdGroupMember -identity ForestManagers  -Credential $credential  -Server iprod.nsomnia.io
Get-AdGroupMember -identity ForestManagers -Credential $credential -Server iprod.nsomnia.io | select name
Get-ADUser -Identity mspdb -Properties * -Credential $credential -Server iprod.nsomnia.io  
Get-ADUser -Filter 'Name -like "*mspdb"' -Credential $credential -Server iprod.nsomnia.io  | Format-Table Name,SamAccountName -A
Get-ADForest -Identity  iprod.nsomnia.io  -Credential $credential
Get-ADForest -Credential $credential -Server iprod.nsomnia.io 
Get-ADTrust -Credential $credential -Filter "Target -eq 'iprod.nsomnia.io'"
Get-ADTrust -Credential $credential -Identity "iprod.nsomnia.io"
```

### Get Domain Computers

```
Get-ADComputer -Filter * -Properties * | Select -Property Name,DNSHostName,Enabled,LastLogonDate,IPv4Address,OperatingSystemVersion | Format-Table
powershell ([adsisearcher]"objectclass=computer").FindAll().Properties.name
powershell Get-WmiObject -Namespace root\directory\ldap -Class ds_computer | select -ExpandProperty ds_cn
```
### Get Domain Users
```
powershell Get-WmiObject -Class Win32_UserAccount | select name 
powershell Get-WmiObject -Class Win32_UserAccount | select caption,SID,name

```
### User Identify
```
powershell [System.Security.Principal.WindowsIdentity]::GetCurrent() | Format-Table -auto
powershell ([adsisearcher]'(samaccountname=n.glover)').FindOne().Properties.memberof

```
### Get Domain Admin
```
powershell ([adsisearcher]"(&(objectClass=User)(admincount=1))").FindAll().Properties.samaccountname
```
### Get Domain Groups
```
powershell Get-WmiObject -Class Win32_Group
powershell Get-WmiObject -Class Win32_GroupInDomain | Foreach-Object {[wmi]$_.PartComponent}
powershell Get-WmiObject -Class Win32_GroupInDomain | where-object {$_.GroupComponent -match "domain"} | foreach-object {[wmi]$_.PartComponent}  

```
### Get Domain Admins Group Members
```
powershell Get-WmiObject -Class Win32_GroupUser | where-object {$_.GroupComponent -match "Domain Admins"} | foreach-object {[wmi]$_.PartComponent}  
powershell Get-WmiObject -Class Win32_GroupUser | where-object {$_.GroupComponent -match "Enterprise Admins"} | foreach-object {[wmi]$_.PartComponent}
powershell Get-WmiObject -Class Win32_GroupUser | where-object {$_.GroupComponent -match "Helpdesk"} | foreach-object {[wmi]$_.PartComponent}

```


###  Search for all users that do not have homedirectory attribute set
```
powershell ([adsisearcher]'(!homedirectory=*)').FindAll()
powershell ([adsisearcher]'(&(objectcategory=user)(!homedirectory=*))').FindAll()
powershell ([adsisearcher]'(&(objectcategory=user)(!homedirectory=*))').FindAll().Count
```
### Get Current Domain
```
powershell [System.DirectoryServices.ActiveDirectory.Domain]::GetCurrentDomain()
powershell [System.DirectoryServices.ActiveDirectory.Forest]::GetCurrentForest() 
```
### Get Domain Trusts
```
powershell ([System.DirectoryServices.ActiveDirectory.Domain]::GetCurrentDomain()).GetAllTrustRelationships() 
```

### SQL
```
powershell [System.Data.Sql.SqlDataSourceEnumerator]::Instance.GetDataSources()
```
### Constrained Delegation
```
powershell Get-ADComputer -Filter {(msDS-AllowedToDelegateTo -ne "{}")} -Properties TrustedForDelegation,TrustedToAuthForDelegation,ServicePrincipalName,Description,msDS-AllowedToDelegateTo
```


### Get Local Route Table
```
powershell Get-WmiObject -Class Win32_IP4RouteTable | select description, nexthop 

```

### Updated
```
#Domain Enumeration
[System.Net.Dns]::GetHostByName(($env:computerName))
[System.DirectoryServices.ActiveDirectory.Domain]::GetCurrentDomain()

#Domain Forest Trusts
([System.DirectoryServices.ActiveDirectory.Domain]::GetCurrentDomain()).GetAllTrustRelationships()
([System.DirectoryServices.ActiveDirectory.Forest]::GetCurrentForest())
([ADSISearcher]"(objectClass=trustedDomain)").FindAll()
([ADSISearcher]"(objectClass=trustedDomain)").FindAll() | %{$a=$_.Properties["trustattributes"]; $d=$_.Properties["trustdirection"]; $t=$_.Properties["trusttype"] ; write-Host $_.Properties["distinguishedname"] $a $d $t}


#Get a Domain Computer
([ADSISearcher]"ObjectClass=computer").FindAll()
([ADSISearcher]"(&(objectClass=computer)(name=Man*))").FindAll()
([ADSISearcher]"(&(objectClass=computer)(name=Manmeet))").FindAll()
([adsisearcher]'(&(objectCategory=computer)(!(description=*)))').FindAll()
([adsisearcher]'(&(objectCategory=group)(description=*))').FindAll()

([adsisearcher]'(&(objectCategory=person)(objectClass=user)
(userAccountControl:1.2.840.113556.1.4.803:=544))').FindAll()

#LAPS
([adsisearcher]'(&(objectCategory=computer)(ms-MCSAdmPwd=*))').FindAll().properties
([adsisearcher]"(&(objectCategory=computer)(ms-MCS-AdmPwd=*)(sAMAccountName=*))").findAll() | ForEach-Object { $_.properties}
([adsisearcher]"(&(objectCategory=computer)(ms-MCS-AdmPwd=*)(sAMAccountName=MACHINE$))").findAll() | ForEach-Object { $_.properties}





([adsisearcher]'(&(objectCategory=user) (badpwdcount>=1))').FindAll()


#Enumerate All Users

([ADSISearcher]"(&(objectClass=user (samAccountType=805306368))").FindAll()|ft

([ADSISearcher]"(&(objectClass=user)(samAccountType=805306368))").FindAll() | %{ $_.Properties["samaccountname"] }

#Enumerate all users with a SPN
([ADSISearcher]"(&(objectClass=user)(servicePrincipalName=*)(samAccountType=805306368))").FindAll()

#Enumerate a Domain Group
([ADSISearcher]"ObjectClass=group").FindAll()
([ADSISearcher]"(&(ObjectClass=group)(samaccountname=Domain Admins))").FindOne()
([ADSISearcher]"(distinguishedname=CN=AB ACCESS,CN=Users,DC=corp,DC=manmeetdc,DC=local)").FindOne().Properties.member

 All organizational units
([adsisearcher]'(objectCategory=organizationalUnit)').FindAll()

All containers
([adsisearcher]'(objectCategory=container)').FindAll()
```
