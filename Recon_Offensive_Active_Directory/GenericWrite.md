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
```
Get-DomainObjectAcl -Identity machineadmins -ResolveGUIDs | ForEach-Object {$_ | Add-Member NoteProperty 'IdentityName' $(Convert-SidToName $_.SecurityIdentifier);$_} | ?{$_.IdentityName -match 'managers'}
```
us\managers group does have some interesting permissions. 
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
