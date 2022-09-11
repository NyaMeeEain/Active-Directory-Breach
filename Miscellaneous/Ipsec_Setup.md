
vim /etc/ipsec.conf 
```
conn test
	authby=psk
	auto=start
	esp=3des-sha1
	ike=3des-sha1-modp1024
	keyexchange=ikev1
	type=transport
	right=192.168.100.199
	rightsubnet=192.168.100.199[tcp/]
  ```
