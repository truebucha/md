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



