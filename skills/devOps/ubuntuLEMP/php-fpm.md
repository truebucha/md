# php-fpm

* `systemctl status php7.4-fpm.service`

* `systemctl restart php7.4-fpm`

* run location `/run/php/php7.4-fpm.sock`

* `ps aux | grep php-fpm`

* edit `cd /etc/php/7.4/fpm/pool.d` `www.conf` default user -> www-data

```
user = www-data
group = www-data
listen.owner = dfire
listen.group = dfire
;listen.acl_users = dfire not working ?? why
```

* `listen.acl_users = apache,nginx,myuser`

* `sudo apt install libfcgi-bin`

* `access.log = /var/log/$pool.access.log`

`cat /var/log/www.access.log`

example:

```
- -  04/Sep/2021:10:27:54 +0000 "GET /s/index.php" 200
```

then 

```
SCRIPT_NAME=/index.php \
SCRIPT_FILENAME=/var/www/dg-site/index.php \
REQUEST_METHOD=GET \
QUERY_STRING=param1=x\&param2=y \
cgi-fcgi -bind -connect /run/php/php7.4-fpm.sock
```
