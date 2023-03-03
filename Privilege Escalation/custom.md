### Custom LPE

```
sc create MeMe binPath= "C:\test\accesschk64.exe" DisplayName= "MeMe" start= auto
icacls "C:\test\accesschk64.exe" /grant Everyone:F /inheritance:e /T
```
