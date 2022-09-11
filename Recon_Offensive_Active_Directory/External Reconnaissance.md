### External Reconnaissance
The initial reconnaissance of a target enables you to understand the organization about people and technology and Obtaining  a list of emaill addresses and employee name. 


```
host -v -a acmebank.xyz
dig acmebank.xyz +short
```

### Identify CloudFront and Ip Version 6 Addresses
```
dig +short IN AAAA acmebank.xyz

```


### Google Dork OSINT Collection
```
filetype:"xls | xlsx | doc | docx | txt | pdf" site:citibank.com
filetype:"xls | xlsx | doc | docx | txt | pdf" site:kbzbank.com
site:linkedin.com -inurl:dir "at **citi**" "Current"
site:linkedin.com -inurl:dir "at **citi**" "Current" **security**
site:linkedin.com -inurl:dir "at **citi**" "Current" **database**
site:http://linkedin.com/in "security" "at **citi**" "Current"
s3 site:http://amazonaws.com filetype:"xls | xlsx | doc | docx | txt | pdf"  password

```

### Email Format Generate 
Unless we identify useable emails during our reconnaissance of a target.namemash tools allow us to generate a various types of emaill address by given a list of user.
```
cat taret.txt
John Steve
Tun Sanda
Karmar Khaing
Soe Thurein

namemash.py taret.txt | sed 's/$/@acmebank.xyz/g' > emails.txt
```
