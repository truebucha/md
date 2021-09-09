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
    location / {
        return 301 https://$host$request_uri;
    }
}
```