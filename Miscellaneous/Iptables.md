### Iptable
```
sudo iptables -A INPUT -p tcp -s 203.0.113.0/24 --dport 22 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
sudo iptables -A OUTPUT -p tcp --sport 22 -m conntrack --ctstate ESTABLISHED -j ACCEPT

sudo iptables -A INPUT -p tcp --dport 80 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
sudo iptables -A OUTPUT -p tcp --sport 80 -m conntrack --ctstate ESTABLISHED -j ACCEPT

sudo iptables -A INPUT -p tcp --dport 443 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
sudo iptables -A OUTPUT -p tcp --sport 443 -m conntrack --ctstate ESTABLISHED -j ACCEPT

sudo iptables -A INPUT -p tcp -m multiport --dports 80,443 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
sudo iptables -A OUTPUT -p tcp -m multiport --dports 80,443 -m conntrack --ctstate ESTABLISHED -j ACCEPT

iptables -N antiscan
iptables -A antiscan -s 172.16.242.34 -j ACCEPT
iptables -A antiscan -j DROP
iptables -I INPUT -m tcp -p tcp --dport 22 -j antiscan
iptables -I INPUT -m tcp -p tcp --dport 8080 -j antiscan
iptables -I INPUT -m tcp -p tcp --dport 8081 -j antiscan
iptables -I INPUT -m udp -p udp --dport 111 -j antiscan
iptables -I INPUT -m udp -p udp --dport 161 -j antiscan
service iptables save
```
