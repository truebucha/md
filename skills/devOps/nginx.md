# guides

<https://www.nginx.com/resources/wiki/start/topics/tutorials/config_pitfalls/>

<http://nginx.org/en/docs/http/ngx_http_fastcgi_module.html#fastcgi_split_path_info>

- [x] [Setup nGinx with server blocks](https://www.digitalocean.com/community/tutorials/how-to-install-nginx-on-ubuntu-18-04#step-5-setting-up-server-blocks-(recommended))

- [ ] [Setup SSL with let's incrypt](https://www.digitalocean.com/community/tutorials/how-to-secure-nginx-with-let-s-encrypt-on-ubuntu-18-04)


# dirs

* /etc/nginx/

* /var/www/

## sites config

`/etc/nginx/sites-enabled/default` - locations config for the nginx

`sudo nano /etc/nginx/sites-enabled/default` - edit

## reload

`sudo service nginx reload` or 

```
sudo systemctl daemon-reload // looks like redundant
sudo systemctl reload nginx
```

## status

`sudo systemctl status nginx.service`

## logs

`cat /var/log/nginx/access.log`

`cat /var/log/nginx/error.log`

## check config

`sudo nginx -t`

## config

`/etc/nginx/`

```
user  nginx;
worker_processes auto;

error_log  /var/log/nginx/error.log warn;
pid        /var/run/nginx.pid;

events {
    worker_connections 4000;
    multi_accept on;
}
worker_rlimit_nofile 64000;


http {
    include       /etc/nginx/mime.types;
    default_type  application/octet-stream;

    log_format  main  '$remote_addr - $remote_user [$time_local] "$request" '
                      '$status $body_bytes_sent "$http_referer" '
                      '"$http_user_agent" "$http_x_forwarded_for"';

    access_log  /var/log/nginx/access.log  main;

    sendfile        on;
    #tcp_nopush     on;

    keepalive_timeout  65;

    #gzip  on;

    include /etc/nginx/conf.d/*.conf;
}
```

`sites-available/default`

```
server {
    listen [::]:443 ssl ipv6only=on; # managed by Certbot
    listen 443 ssl; # managed by Certbot
    ssl_certificate /etc/letsencrypt/live/www.detecta.group/fullchain.pem; # managed by Certbot
    ssl_certificate_key /etc/letsencrypt/live/www.detecta.group/privkey.pem; # managed by Certbot
    include /etc/letsencrypt/options-ssl-nginx.conf; # managed by Certbot
    ssl_dhparam /etc/letsencrypt/ssl-dhparams.pem; # managed by Certbot

    server_name www.detecta.group detecta.group;
    index index.html index.htm index.nginx-debian.html;
    root /var/www/dg-landing-main;

    location ~ /\.ht {
        deny all;
    }
    location / {
        try_files $uri $uri/ =404;
    }
    location /s/ {
        index index.php index.html index.htm;
        alias /var/www/dg-site/;
        location ~ \.php$ {
            try_files $uri =404;
            fastcgi_pass unix:/run/php/php7.4-fpm.sock;
	    fastcgi_split_path_info       ^(.+\.php)(.*)$;
            include fastcgi_params;
            fastcgi_index  index.php;
	    fastcgi_param  SCRIPT_FILENAME  $request_filename;
        }
    }
    location /api/1/ {
        proxy_pass http://localhost:3030/;
    }
    #location /test {
    #    alias /var/www/test/;
    #}
    #location /test/1 {
    #    alias /var/www/test/1/dg-landing-main/;
    #}
    #location /cv/kanstantsinbucha {
    #    alias /var/www/cv/kanstantsinbucha/cv-svelte-prod-build/;
    #}
}
server {
    listen 80;
    listen [::]:80;
    server_name www.detecta.group detecta.group;
    location /api/1/ {
        proxy_pass http://localhost:3030/;
    }
}
```

