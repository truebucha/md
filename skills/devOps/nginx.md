# guides

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
sudo systemctl restart nginx
```

## status

`sudo systemctl status nginx.service`

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

