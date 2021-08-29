# droplets

## digital ocean


# production

<https://www.digitalocean.com/community/tutorials/how-to-set-up-a-node-js-application-for-production-on-ubuntu-20-04>

## SSL

- [ ] <https://www.digitalocean.com/community/tutorials/how-to-secure-nginx-with-let-s-encrypt-on-ubuntu-18-04>

## nodejs 
```
cd ~
curl -sL https://deb.nodesource.com/setup_14.x -o nodesource_setup.sh
sudo bash nodesource_setup.sh
sudo apt install nodejs
nodejs -v
```

## pm2
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
