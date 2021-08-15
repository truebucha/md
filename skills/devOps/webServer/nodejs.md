# nginx + feathers deploy to heroku guide

hotshot: 

```commandline
git add --all && git ci --amend && git push -f heroku master && sleep 5 && heroku logs
```

Setup

1 Add two buildpacks to heroku app

[buildpack](https://github.com/ryandotsmith/nginx-buildpack)

heroku/nodejs

2 provide a custom config for nginx

./config/nginx.conf.erb in your project

Line server localhost:8080 fail_timeout=0; should be corrected to fit the your node app listening port

```ruby
daemon off;
#Heroku dynos have at least 4 cores.
worker_processes <%= ENV['NGINX_WORKERS'] || 4 %>;

events {
	use epoll;
	accept_mutex on;
	worker_connections 1024;
}

http {
       gzip on;
       gzip_comp_level 2;
       gzip_min_length 512;

	server_tokens off;

	log_format l2met 'measure#nginx.service=$request_time request_id=$http_x_request_id';
	access_log logs/nginx/access.log l2met;
	error_log logs/nginx/error.log;

	include mime.types;
	default_type application/octet-stream;
	sendfile on;

	#Must read the body in 5 seconds.
	client_body_timeout 5;

   # app only
	#upstream app_server {
   #  server 127.0.0.1:8080 fail_timeout=0;
	#}
	
	# web socket to
	upstream socket_nodes {
     ip_hash;
  server 127.0.0.1:8080 fail_timeout=0 weight=5;
	}

	server {
  listen <%= ENV["PORT"] %>;
  server_name _;
  keepalive_timeout 5;

  location / {
      proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
           proxy_set_header Host $host;
           
   # app only
   #proxy_redirect off;
   #proxy_pass http://app_server;
   
   # web socket too
   proxy_set_header Upgrade $http_upgrade;
           proxy_set_header Connection "upgrade";
           proxy_http_version 1.1;
           proxy_pass http://socket_nodes;
  }
	}
}
```


3 run your node feathers app on chosed port and touch /tmp/app-initialized when ready

./src/index.js

Replace content with  this code
Function touch pushed nginx to start (it waits while your app touched “/tmp/app-initialized” file)

And we select the same port to listen that we chosed in nginx config: 8080


```javascript
'use strict';

const FS = require('fs');
const PATH = require('path');
const APP = require('./app');

function touch (file) {
 let filePath = PATH.normalize(PATH.join(file));
 console.log('touching file at ' + filePath);
 let fd = FS.openSync(filePath, 'w');
 let timestamp = Math.round(Date.now()/1000);
 FS.futimesSync(fd, timestamp, timestamp);
 FS.closeSync(fd);
 console.log('touched file at ' + filePath);
}

//let port = (process.env.PORT || 5000);
let port = 8080;

console.log('starting on port: ' + port);
//app.set('port', port);
//const port = app.get('port');
const SERVER = APP.listen(port);
console.log ('listening');
SERVER.on('listening', function onListening () {
 let host = APP.get('host');
 console.log('Feathers application started on '+ host + ':' + port);
 touch('/tmp/app-initialized');
});
console.log ('connected onListening');

4 add Procfile to root of your project
./Procfile
web: bin/start-nginx node src/index.js
5 go to yours Package.json
./package.json
And select right engine version (now feathers use 5.10.1)
 "engines": {
   "node": "5.10.1"
 }
6 correct your feathers production config ./config/production.js
./config/production.js
{
 "host": "featherstest-app.feathersjs.com",
 "port": 8080,
 "nedb": "NEDB_BASE_PATH",
 "public": "../public/",
 "auth": {
   "token": {
     "secret": "FEATHERS_AUTH_SECRET"
   },
   "local": {}
 }
}
```

7 use heroku deploy guide to push changes

You need to instal heroku [cli](https://toolbelt.heroku.com/):

Than navigate to your project dir

Open command line and processed:
```commandline
$ heroku login
$ git init
$ heroku git:remote -a your_app_name
```

And push a changes to begin deploy

```commandline
git add --all && git ci -m”initial” && git push heroku master && sleep 5 && heroku logs
```

I use a test sequence to force push same commit to deploy until it succeed

```commandline
git add --all && git ci --amend --no-edit && git push -f heroku master && sleep 5 && heroku logs
```

# links

[настройка nginx + let's encrypt (free ssl)](https://habrahabr.ru/post/306128/)


[wallarm.com](https://wallarm.com) security

[Use nginx like reverse proxy](https://www.nginx.com/blog/5-performance-tips-for-node-js-applications/)

[Use node.js express framework](https://expressjs.com/en/guide/behind-proxies.html)

[Feathers for build RESTful API](http://feathersjs.com)

[Soket.IO vs REST](http://blog.arungupta.me/rest-vs-websocket-comparison-benchmarks/)

[websockets-vs-rest](https://www.pubnub.com/blog/2015-01-05-websockets-vs-rest-api-understanding-the-difference/)

[Scalable webSocket (socket.io) app](http://goldfirestudios.com/blog/136/Horizontally-Scaling-Node.js-and-WebSockets-with-Redis)

Some load balancing features

Postponed

Swift implementation

Vapor pure swift webserver

https://github.com/qutheory/vapor

Heroku buildpack for swift package manager based apps

https://github.com/kylef/heroku-buildpack-swift