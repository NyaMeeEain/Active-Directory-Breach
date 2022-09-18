```
Let's remove default configuration's symlink from sites-enabled:
sudo unlink /etc/nginx/sites-enabled/default

cd /etc/nginx/sites-available/
Let's create our configuration file under sites-available:
nano reverse-proxy.conf

Now we need to create a symlink under sites-enabled
sudo ln -s /etc/nginx/sites-available/reverse-proxy.conf /etc/nginx/sites-enabled/reverse-proxy.conf

sudo nginx -t
sudo systemctl reload nginx
```
