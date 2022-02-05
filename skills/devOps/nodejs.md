
# Setup

## Mac Using NVM

``` cmd

touch ~/.bash_profile
curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.32.1/install.sh | bash

```

## Installing Using NVM

An alternative to installing Node.js with apt is to use a tool called nvm, which stands for "Node.js Version Manager". Rather than working at the operating system level, nvm works at the level of an independent directory within your home directory. This means that you can install multiple self-contained versions of Node.js without affecting the entire system.

Controlling your environment with nvm allows you to access the newest versions of Node.js and retain and manage previous releases. It is a different utility from apt, however, and the versions of Node.js that you manage with it are distinct from the versions you manage with apt.

To download the nvm installation script from the project's GitHub page, you can use curl. Note that the version number may differ from what is highlighted here:

```cmd

curl -sL https://raw.githubusercontent.com/creationix/nvm/v0.33.11/install.sh -o install_nvm.sh

```

Inspect the installation script with nano:

```cmd

nano install_nvm.sh

```

Run the script with bash:

```cmd

bash install_nvm.sh

```

It will install the software into a subdirectory of your home directory at ~/.nvm. It will also add the necessary lines to your ~/.profile file to use the file.

To gain access to the nvm functionality, you'll need to either log out and log back in again or source the ~/.profile file so that your current session knows about the changes:

```cmd

source ~/.profile

```

With nvm installed, you can install isolated Node.js versions. For information about the versions of Node.js that are available, type:

```cmd

nvm ls-remote

```

Output

```cmd

...
         v8.11.1   (Latest LTS: Carbon)
         v9.0.0
         v9.1.0
         v9.2.0
         v9.2.1
         v9.3.0
         v9.4.0
         v9.5.0
         v9.6.0
         v9.6.1
         v9.7.0
         v9.7.1
         v9.8.0
         v9.9.0
        v9.10.0
        v9.10.1
        v9.11.0
        v9.11.1
        v10.0.0  
        
```

As you can see, the current LTS version at the time of this writing is v8.11.1. You can install that by typing:

```cmd

nvm install 8.11.1

```

Usually, nvm will switch to use the most recently installed version. You can tell nvm to use the version you just downloaded by typing:

```cmd

nvm use 8.11.1

```

When you install Node.js using nvm, the executable is called node. You can see the version currently being used by the shell by typing:

```cmd

node -v

```

Output

```cmd

v8.11.1

```

If you have multiple Node.js versions, you can see what is installed by typing:

```cmd

nvm ls

```

If you wish to default one of the versions, type:

```cmd

nvm alias default 8.11.1

```

This version will be automatically selected when a new session spawns. You can also reference it by the alias like this:

nvm use default
Each version of Node.js will keep track of its own packages and has npm available to manage these.

You can also have npm install packages to the Node.js project's ./node_modules directory. Use the following syntax to install the express module:

```cmd

npm install express

```

If you'd like to install the module globally, making it available to other projects using the same version of Node.js, you can add the -g flag:

```cmd

npm install -g express

```

This will install the package in:

```cmd

~/.nvm/versions/node/node_version/lib/node_modules/express

```

Installing the module globally will let you run commands from the command line, but you'll have to link the package into your local sphere to require it from within a program:

```cmd

npm link express

```

You can learn more about the options available to you with nvm by typing:

```cmd

nvm help

```

## Installing Using a PPA

To get a more recent version of Node.js you can add the PPA (personal package archive) maintained by NodeSource. This will have more up-to-date versions of Node.js than the official Ubuntu repositories, and will allow you to choose between Node.js v6.x (supported until April of 2019), Node.js v8.x (the current LTS version, supported until December of 2019), Node.js v10.x (the second current LTS version, supported until April of 2021), and Node.js v11.x (the current release, supported until June 2019).

First, install the PPA in order to get access to its contents. From your home directory, use curl to retrieve the installation script for your preferred version, making sure to replace 10.x with your preferred version string (if different):

```cmd 

cd ~

curl -sL https://deb.nodesource.com/setup_10.x -o nodesource_setup.sh

```
You can inspect the contents of this script with nano (or your preferred text editor):

```cmd 

nano nodesource_setup.sh

```

Run the script under sudo:

sudo bash nodesource_setup.sh
The PPA will be added to your configuration and your local package cache will be updated automatically. After running the setup script from Nodesource, you can install the Node.js package in the same way you did above:

```cmd 

sudo apt install nodejs

```

To check which version of Node.js you have installed after these initial steps, type:

```cmd 

nodejs -v

```

Output

```cmd 

v10.14.0

```

The nodejs package contains the nodejs binary as well as npm, so you don't need to install npm separately.

npm uses a configuration file in your home directory to keep track of updates. It will be created the first time you run npm. Execute this command to verify that npm is installed and to create the configuration file:

```cmd 

npm -v

```

Output

```cmd 

6.4.1

```

In order for some npm packages to work (those that require compiling code from source, for example), you will need to install the build-essential package:

```cmd 

sudo apt install build-essential

```

You now have the necessary tools to work with npm packages that require compiling code from source.

## Removing Node.js

You can uninstall Node.js using apt or nvm, depending on the version you want to target. To remove the distro-stable version, you will need to work with the apt utility at the system level.

To remove the distro-stable version, type the following:

```cmd

sudo apt remove nodejs

```

This command will remove the package and retain the configuration files. These may be of use to you if you intend to install the package again at a later point. If you don’t want to save the configuration files for later use, then run the following:

```cmd

sudo apt purge nodejs

```

This will uninstall the package and remove the configuration files associated with it.

As a final step, you can remove any unused packages that were automatically installed with the removed package:

```cmd

sudo apt autoremove

```

To uninstall a version of Node.js that you have enabled using nvm, first determine whether or not the version you would like to remove is the current active version:

```cmd

nvm current

```

If the version you are targeting is not the current active version, you can run:

```cmd

nvm uninstall node_version

```

This command will uninstall the selected version of Node.js.

If the version you would like to remove is the current active version, you must first deactivate nvm to enable your changes:

```cmd

nvm deactivate

```

You can now uninstall the current version using the uninstall command above, which will remove all files associated with the targeted version of Node.js except the cached files that can be used for reinstallment.


# Project Structuring

When I started building Node & Express applications, I didn’t know how important it was to structure your application. Express doesn’t come with strict rules or guidelines for maintaining the project structure.
You are free to use any structure you want. When your codebase grows you end up having long route handlers. This makes your code hard to understand and it contains potential bugs.
If you’re working for a startup, most of the time you won’t have time to refractor your project or modularize it. You can end up with an endless loop of bug fixing and patching.

Over time, while working with both small teams and large teams, I realized what kind of structure can grow with your project and still be easy to maintain.

## Model View Controller

The MVC pattern helps in rapid and parallel development. For example, one developer can work on the view, while another one can work on creating the business logic in the controller.
Let’s take a look at an example of a simple user CRUD application.

```

project/
  controllers/
    users.js
  util/
    plugin.js
  middlewares/
    auth.js
  models/
    user.js
  routes/
    user.js
    router.js
  public/
    js/
    css/
    img/
  views/
    users/
      index.jade
  tests/
    users/
      create-user-test.js 
      update-user-test.js
      get-user-test.js
  .gitignore
  app.js
  package.json

```

* controllers: Define your app route handlers and business logic

* util: Writes utility/helper functions here which can be used by any controllers. For example, you can write a function like mergeTwoArrays(arr1, arr2).

* middlewares: You can write middlewares to interpret all incoming requests before moving to the route handler. For example, 

```

 router.post('/login', auth, controller.login) where auth is a middleware function defined in middlewares/auth.js.
 
```
* models: also a kind of middleware between your controller and the database. You can define a schema and do some validation before writing to the database. For example, you can use an ORM like Mongoose which comes with great features and methods to use in the schema itself

* routes: Define your app routes, with HTTP methods. For example, you can define everything related to the user.

```

router.post('/users/create', controller.create)
router.put('/users/:userId', controller.update)
router.get('/users', controller.getAll)

```

* public: Store static images in/img, custom JavaScript files, and CSS /css

* views: Contains templates to be rendered by the server.

* tests: Here you can write all the unit tests or acceptance tests for the API server.

* app.js: Acts as the main file of the project where you initialize the app and other elements of the project.

* package.json: Takes care of the dependencies, the scripts to run with the npm command, and the version of your project.

## Exceptions and Error Handling

This is one of the most important aspects to think about when creating any project with any language. Let’s see how to handle errors and exceptions gracefully in an Express app.

* Using promises

One of the advantages of using promises over callbacks is they can handle implicit or explicit exceptions/errors in asynchronous code blocks as well as for synchronous code defined in .then(), a promise callback
Just add .catch(next) at the end of the promise chain. For example:

```

router.post('/create', (req, res, next) => {
   User.create(req.body)    // function to store user data in db
   .then(result => {
     // do something with result
    
     return result 
   })
   .then(user => res.json(user))
   .catch(next)
})

```

* Using try-catch

Try-catch is a traditional way of catching exceptions in asynchronous code.
Let’s take a look at an example with a possibility of getting an exception:

```

router.get('/search', (req, res) => {
 
  setImmediate(() => {
    const jsonStr = req.query.params
    try {
      const jsonObj = JSON.parse(jsonStr)
      
      res.send('Success')
    } catch (e) {
      res.status(400).send('Invalid JSON string')
    }
  })
})

```

## Avoid using synchronous code

Synchronous code also known as blocking code, because it blocks the execution until they are executed.

So avoid using synchronous functions or methods that might take milliseconds or microseconds. For a high traffic website it will compound and may lead to high latency or response time of the API requests.

Don’t use them in production especially :)

Many Node.js modules come with both .sync and .async methods, so use async in production.

But, if you still want to use a synchronous API use --trace-sync-io command-line flag. It will print a warning and a stack trace whenever your application uses a synchronous API.

For more on the fundamentals of error handling, see:

## Error Handling in Node.js

Building Robust Node Applications: Error Handling (StrongLoop blog)

What you should not do is to listen for the uncaughtException event, emitted when an exception bubbles all the way back to the event loop. Using it is generally not preferred.

## Logging properly

Logging is essential for debugging and app activity. It is used mainly for development purposes. We use console.log and console.error but these are synchronous functions.

## For Debugging purposes

You can use a module like debug. This module enables you to use the DEBUG environment variable to control what debug messages are sent to console.err(), if any.

## For app activity

One way is to write them to the database.

Check out How I used mongoose plugins to do auditing of my application .

Another way is to write to a file OR use a logging library like Winston or Bunyan. For a detailed comparison of these two libraries, see the StrongLoop blog post Comparing Winston and Bunyan Node.js Logging.

## require(“./../../../../../../”) mess

There are different workarounds for this problem.

If you find any module getting popular and if it has logical independence from the application, you can convert it to private npm module and use it like any other module in package.json.

OR

```

const path  = require('path');
const HOMEDIR  = path.join(__dirname,'..','..');
where __dirname is the built-in variable that names the directory that contains the current file, and .. ,..is the requisite number of steps up the directory tree to reach the root of the project.

```

From there it is simply:


```

const foo = require(path.join(HOMEDIR,'lib','foo'));
const bar = require(path.join(HOMEDIR,'lib','foo','bar'));

```

to load an arbitrary file within the project.

Let me know in the comment below if you have better ideas :)

## Set NODE_ENV to “production”

The NODE_ENV environment variable specifies the environment in which an application is running (usually, development or production). One of the simplest things you can do to improve performance is to set NODE_ENVto “production.

Setting NODE_ENV to “production” makes Express:

* Cache view templates.

* Cache CSS files generated from CSS extensions.

* Generate less verbose error messages.

Tests indicate that just doing this can improve app performance by a factor of three!

## Using Process Manager

For production, you should not simply use node app.j — if your app crashes, it will be offline until you restart it.

The most popular process managers for Node are:

* StrongLoop Process Manager
* PM2
* Forever

I personally use PM2.

For a feature-by-feature comparison of the three process managers, see http://strong-pm.io/compare/. For a more detailed introduction to all three, see Process managers for Express apps.

## Run your app in a cluster

In a multi-core system, you can increase the performance of a Node app by many times by launching a cluster of processes.

A cluster runs multiple instances of the app, ideally one instance on each CPU core. This distributes the load and tasks among the instances.

## Using Node’s cluster module

Clustering is made possible with Node’s cluster module. This enables a master process to spawn worker processes. It distributes incoming connections among the workers.

However, rather than using this module directly, it’s far better to use one of the many tools out there that do it for you automatically. For example node-pm or cluster-service.

### Using PM2

For pm2 you can use cluster directly through a command. For example,

Start 4 worker processes

```cmd 

pm2 start app.js -i 4

```cmd

Auto-detect number of available CPUs and start that many worker processes

```cmd 

pm2 start app.js -i max 

```


