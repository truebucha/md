# terminal shell job managment

[source](http://www.tldp.org/LDP/abs/html/x9644.html)
bg, fg, jobs, kill, killall

# Making a SSH Key

If you already have an existing SSH key, you can use it for Fedora work.

In that case, proceed to Step 2 in the following procedure.

If you do not have a SSH key yet, start with the first step below:

Enter the following command:


```
ssh-keygen -t rsa
```

Accept the default location (~/.ssh/id_rsa) and enter a passphrase.

Remember Your Passphrase

You must have your passphrase to commit translations. It cannot be recovered if you forget it.

Change permissions to your key and .ssh directory:


```
chmod 700 ~/.ssh 
chmod 600 ~/.ssh/id_rsa
chmod 644 ~/.ssh/id_rsa.pub
```

This public key (~/.ssh/id_rsa.pub) will be used for your Fedora account creation described in Section 1.4, “Applying for an Account”.

# Config file


```

Host bitbucket.org
    Hostname bitbucket.org
    User truebucha
    UseKeychain yes
    AddKeysToAgent yes
    PubKeyAuthentication yes
    IdentityFile ~/.ssh/bitbucket

Host bitbucket-estbyright
	User estbyright_gfa
   	Hostname bitbucket.org
    UseKeychain yes
   	AddKeysToAgent yes
    PubKeyAuthentication yes
	IdentityFile ~/.ssh/green_rsa

Host github.com
   	Hostname github.com
    User truebucha
	UseKeychain yes
   	AddKeysToAgent yes
    PubKeyAuthentication yes
    IdentityFile ~/.ssh/github
        
```