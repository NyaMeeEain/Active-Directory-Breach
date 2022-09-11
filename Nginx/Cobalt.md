```
stream {
    upstream ssl {
        server 192.168.99.5:443;
    }

    upstream http {
        server 192.168.99.5:80;
    }

    upstream dns {
        server 192.168.99.5:53;
    }

    server {
        listen 443;
        proxy_pass ssl;
    }

    server {
	listen 80;
	proxy_pass http;
    }

    server {
	listen 53;
	proxy_pass dns;
    }

    server {
	listen 53 udp;
	proxy_pass dns;
    }

}
```
