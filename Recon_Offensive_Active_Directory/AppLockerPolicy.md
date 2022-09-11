# AppLockerPolicy
```
Get-ApplockerPolicy -Effective -xml
Get-AppLockerPolicy -Effective | select -ExpandProperty RuleCollections
$a = Get-ApplockerPolicy -effective
$a.rulecollections
```

Credit @https://book.hacktricks.xyz/windows/basic-powershell-for-pentesters#applockerpolicy
