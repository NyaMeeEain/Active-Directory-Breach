
***One of the easiest ways to find exploitable paths, is to mark your current user (or machine account) as owned and perform the Shortest Paths from Owned Principles built-in query.***

```
atch (n:User) return n
Match (n:Computer) return n

MATCH (u:User {owned:true}), (g:Group), p=(u)-[:MemberOf]->(g) RETURN p
MATCH p=(a:Computer)-[r:HasSession]->(b:User) WITH a,b,r MATCH p=shortestPath((b)-[:AdminTo|MemberOf*1..]->(a)) RETURN p
MATCH (n:User),(m:Computer), (n)<-[r:HasSession]-(m) WHERE NOT n.name STARTS WITH 'ANONYMOUS LOGON' AND NOT n.name='' WITH n, count(r) as rel_count order by rel_count desc LIMIT 10 MATCH p=(m)-[r:HasSession]->(n) RETURN p
MATCH (n:User),(m:Computer), (n)-[r:AdminTo]->(m) WHERE NOT n.name STARTS WITH 'ANONYMOUS LOGON' AND NOT n.name='' WITH m, count(r) as rel_count order by rel_count desc LIMIT 10 MATCH p=(m)<-[r:AdminTo]-(n) RETURN p


MATCH (c:Computer {unconstraineddelegation:true}) return c
MATCH p=(u:User)-[:AllowedToDelegate]->(c:Computer) RETURN p
MATCH p=(n:User)-[r:MemberOf*1..]->(m:Group {highvalue:true}) RETURN p
MATCH (n:User) MATCH p=allShortestPaths((n)-[r:WriteAccountRestrictions|GenericAll|GenericWrite|Owns|WriteDacl]->(m:Computer)) WHERE n.owned RETURN p
MATCH (a:Computer) MATCH p=allShortestPaths((n)-[r:WriteAccountRestrictions|GenericAll|GenericWrite|Owns|WriteDacl]->(m:Computer)) WHERE n.owned RETURN p

```
Ref: **https://github.com/zblurx/BloodHoundCustomQueries**

### gMSA
```
MATCH p=()-[:ReadGMSAPassword]->() RETURN p
```

### LAPS
```
MATCH (c:Computer {haslaps:true}) RETURN c
MATCH p=(g:Group)-[:ReaLAPSPassword]->(c:Computer) return p

Get-DomainComputer | ? { $_."ms-Mcs-AdmPwdExpirationTime" -ne $null } | select dnsHostName
Get-DomainGPO | ? { $_.DisplayName -like "*laps*" } | select DisplayName, Name, GPCFileSysPath | fl

Get-DomainComputer | Get-DomainObjectAcl -ResolveGUIDs | ? { $_.ObjectAceType -eq "ms-Mcs-AdmPwd" -and $_.ActiveDirectoryRights -match "ReadProperty" } | select ObjectDn, SecurityIdentifier
ConvertFrom-SID S-1-5-21-569305411-121244042-2357301523-1107
ConvertFrom-SID S-1-5-21-569305411-121244042-2357301523-1108
Get-DomainComputer -Identity wkstn-1 -Properties ms-Mcs-AdmPwd
```
