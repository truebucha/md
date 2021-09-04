# droplets

## digital ocean


# production

<https://www.digitalocean.com/community/tutorials/how-to-set-up-a-node-js-application-for-production-on-ubuntu-20-04>

<https://www.digitalocean.com/community/tutorials/how-to-install-linux-nginx-mysql-php-lemp-stack-ubuntu-18-04>

## User by process PID

`ps -u -p 61978`

## users and groups list

`compgen -u`

`compgen -g`

## nodejs 
```
cd ~
curl -sL https://deb.nodesource.com/setup_14.x -o nodesource_setup.sh
sudo bash nodesource_setup.sh
sudo apt install nodejs
nodejs -v
```

## SSL

<https://certbot.eff.org/lets-encrypt/ubuntufocal-nginx>

```
sudo snap install core; sudo snap refresh core
sudo snap install --classic certbot
sudo ln -s /snap/bin/certbot /usr/bin/certbot
sudo certbot --nginx

sudo certbot renew --dry-run

```

## pm2

<https://www.digitalocean.com/community/tutorials/how-to-use-pm2-to-setup-a-node-js-production-environment-on-an-ubuntu-vps>

```
pm2 startup ubuntu
```

create ecosystem by 

```
pm2 ecosystem
```

edit `~/ecosystem.config.js`

```
 module.exports = {
   "apps": [
     {
       "name": "d-cloud",
       "script": "npm",
       "args": "--prefix /var/www/server_app/dg-cloud-app/ run start"
     }
   ]
 };
```

start PM2

```
pm2 start ecosystem.config.js
```

```
pm2 save
```

```
/// Optional
sudo ln -s "$NVM_DIR/versions/node/$(nvm version)/bin/node" "/usr/local/bin/node"
sudo ln -s "$NVM_DIR/versions/node/$(nvm version)/bin/npm" "/usr/local/bin/npm"
```

```
[PM2] Spawning PM2 daemon with pm2_home=/home/dfire/.pm2
[PM2] Restoring processes located in /home/dfire/.pm2/dump.pm2
[PM2] Process /home/dfire/business/dg-dfire-server/app.js restored
```
```
sudo npm install pm2@latest -g
pm2 startup systemd
pm2 start hello.js
```

### Still have issues

```
WARNING: NODE_APP_INSTANCE value of '0' did not match any instance config file names.
WARNING: See https://github.com/lorenwest/node-config/wiki/Strict-Mode
WARNING: NODE_APP_INSTANCE value of '0' did not match any instance config file names.
WARNING: See https://github.com/lorenwest/node-config/wiki/Strict-Mode
```

<https://github.com/lorenwest/node-config/wiki/Strict-Mode>

<https://pm2.keymetrics.io/docs/usage/environment/>

maybe we should create `default-{NODE_APP_INSTANCE}.json` in the `config` directory of the project

with contents
```
{}
```
