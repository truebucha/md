# Install NVM, NodeJS, Yarn via Homebrew

## Getting start

### Part A: Install NVM and NodeJS

1. Install `nvm` via script
    
    $ `curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.37.2/install.sh | bash`
    
2. Add following line to your profile. `.zshrc` 

    ```
    # NVM
    export NVM_DIR="$HOME/.nvm"
    [ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"
    ```
      
4. Verify `nvm` is installed

    $ `nvm --version`
    
5. Check all avaliable version by this command

    $ `nvm ls-remote`
    
6. Install NodeJS (_Recommended to install LTS version. Current LTS is Erbium_)
    
    $ `nvm install --lts=Erbium`
    
7. Check installed NodeJS in your machine.

    $ `nvm ls`
    
8. Set global nodejs version to environment.
    
    $ `nvm use default`
    
See more about `nvm` : https://github.com/creationix/nvm

### Part B: Install Yarn and Linked nvm node to Homebrew

1. Install `yarn` via Homebrew

    $ `brew install yarn`

2. Remove `node` dependencies from Homebrew

    $ `brew uninstall node --ignore-dependencies`

3. Checkout `node` in environment `$PATH` 

    $ `which node`
    
    It should be return => `/User/<your-user-name>/.nvm/versions/node/<latest-node-lts-version>/bin/node`
    
4. Checkout `brew doctor` there should show message **WARNING missing yarn dependencies**
    
    $ `brew doctor`
    
5. Create blank folder and create symbol link `node` folder from `nvm` for `yarn` in Homebrew.

    $ `nvm current` => v12.13.0 (Latest LTS: Erbium) (This should be **Global** node version)
    
    $ `mkdir /usr/local/Cellar/node`
    
    $ `ln -s ~/.nvm/versions/node/$(nvm current)/ /usr/local/Cellar/node`

6. Overwrite `node, npm and npx` from linked `node` in `/usr/local/Cellar/node` to `/usr/local/bin/` homebrew

    $ `brew link --overwrite node`
    
7. Checkout `ls -la /usr/local/bin` to see overwrited `node, npm and npx`
    
8. Checkout `brew doctor` again. There shouldn't have **WARNING** message.

    $ `brew doctor`

9. Prevent Homebrew upgrading node version

    $ `brew pin node`

10. Enjoy ! ❤️

### Part C: Upgrading, To change node.js version and Re-configure Homebrew


1. Checkout `nvm` for to use `node` version (For this example case I will use LTS Erbium)

    $ `nvm list`    

    ```shell 
    $ nvm list
    ->      v12.13.1
            system
    default -> 12.13.1 (-> v12.13.1)
    node -> stable (-> v12.13.1) (default)
    stable -> 12.13 (-> v12.13.1) (default)
    iojs -> N/A (default)
    unstable -> N/A (default)
    lts/* -> lts/erbium (-> v12.13.1)
    lts/argon -> v4.9.1 (-> N/A)
    lts/boron -> v6.17.1 (-> N/A)
    lts/carbon -> v8.16.2 (-> N/A)
    lts/dubnium -> v10.17.0 (-> N/A)
    lts/erbium -> v12.13.1
   ``` 
    \* See more about `nvm` : https://github.com/creationix/nvm


2. Remove the symbol link which we linked `node` in Homebrew `/usr/local/Cellar/node`

    $ `rm -rf /usr/local/Cellar/node`

3. Unpin `node` in Homebrew for upgrading `yarn`

    $ `brew unpin node`

4. Upgrade `yarn`
   
    $ `brew upgrade yarn`

5. Continue on Part B 2. - 10. steps again.

6. Say yay 😝
