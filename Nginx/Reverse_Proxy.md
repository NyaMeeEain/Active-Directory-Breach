```
cd /etc/nginx/conf.d/
nano default.conf
service nginx restart

 
 
server {
  listen 80;
  listen 8080;
  listen 443 ssl;

  server_name proactive.ninja;

  location / {
      proxy_pass https://cisco.com/;
  }

  ssl_certificate /etc/letsencrypt/live/proactive.ninja/fullchain.pem;
  ssl_certificate_key /etc/letsencrypt/live/proactive.ninja/privkey.pem;

}
```
