# use Node Version Manager

<https://github.com/nvm-sh/nvm>

```
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.37.2/install.sh | bash
```



```
nvm alias [version]
```

#use pm2

<https://pm2.keymetrics.io/docs/usage/pm2-doc-single-page/>

```
npm install -g pm2
```

```
pm2 start npm --name "app name" -- start
```

```
pm2 monit
```

# use nginx 

<https://docs.nginx.com/nginx/admin-guide/web-server/>

etc/nginx/sites-enabled/default

```
sudo service nginx restart
```

```
location = /api/1 {
    return 302 /en/;
}
location /api/1/ {
    proxy_pass http://localhost:3030/;  # note the trailing slash here, it matters!
}
```
