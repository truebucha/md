# setup 

## Step 1 — Logging in as Root

To log into your server, you will need to know your server's public IP address. You will also need the password or, if you installed an SSH key for authentication, the private key for the root user's account. If you have not already logged into your server, you may want to follow our guide on how to connect to your Droplet with SSH, which covers this process in detail.

If you are not already connected to your server, go ahead and log in as the root user using the following command (substitute the highlighted portion of the command with your server's public IP address):

```cmd

ssh root@your_server_ip

```

Accept the warning about host authenticity if it appears. If you are using password authentication, provide your root password to log in. If you are using an SSH key that is passphrase protected, you may be prompted to enter the passphrase the first time you use the key each session. If this is your first time logging into the server with a password, you may also be prompted to change the root password.

About Root

The root user is the administrative user in a Linux environment that has very broad privileges. Because of the heightened privileges of the root account, you are discouraged from using it on a regular basis. This is because part of the power inherent with the root account is the ability to make very destructive changes, even by accident.

The next step is to set up an alternative user account with a reduced scope of influence for day-to-day work. We'll teach you how to gain increased privileges during the times when you need them.

## Step 2 — Creating a New User

Once you are logged in as root, we're prepared to add the new user account that we will use to log in from now on.

This example creates a new user called sammy, but you should replace it with a username that you like:

```cmd

adduser sammy

```

You will be asked a few questions, starting with the account password.

Enter a strong password and, optionally, fill in any of the additional information if you would like. This is not required and you can just hit ENTER in any field you wish to skip.

## Step 3 — Granting Administrative Privileges

Now, we have a new user account with regular account privileges. However, we may sometimes need to do administrative tasks.

To avoid having to log out of our normal user and log back in as the root account, we can set up what is known as "superuser" or root privileges for our normal account. This will allow our normal user to run commands with administrative privileges by putting the word sudo before each command.

To add these privileges to our new user, we need to add the new user to the sudo group. By default, on Ubuntu 18.04, users who belong to the sudo group are allowed to use the sudo command.

As root, run this command to add your new user to the sudo group (substitute the highlighted word with your new user):

```cmd

usermod -aG sudo sammy

```

Now, when logged in as your regular user, you can type sudo before commands to perform actions with superuser privileges.

## Step 4 — Setting Up a Basic Firewall

Ubuntu 18.04 servers can use the UFW firewall to make sure only connections to certain services are allowed. We can set up a basic firewall very easily using this application.

Note: If your servers are running on DigitalOcean, you can optionally use DigitalOcean Cloud Firewalls instead of the UFW firewall. We recommend using only one firewall at a time to avoid conflicting rules that may be difficult to debug.

Different applications can register their profiles with UFW upon installation. These profiles allow UFW to manage these applications by name. OpenSSH, the service allowing us to connect to our server now, has a profile registered with UFW.

You can see this by typing:

```cmd

ufw app list

```

Output

```cmd

Available applications:
  OpenSSH
  
```

We need to make sure that the firewall allows SSH connections so that we can log back in next time. We can allow these connections by typing:

```cmd

ufw allow OpenSSH

```

Afterwards, we can enable the firewall by typing:

```cmd

ufw enable

```

Type "y" and press ENTER to proceed. You can see that SSH connections are still allowed by typing:

```cmd

ufw status

```

```cmd

Output
Status: active

To                         Action      From
--                         ------      ----
OpenSSH                    ALLOW       Anywhere
OpenSSH (v6)               ALLOW       Anywhere (v6)

```
As the firewall is currently blocking all connections except for SSH, if you install and configure additional services, you will need to adjust the firewall settings to allow acceptable traffic in. You can learn some common UFW operations in this guide.

## Step 5 — Enabling External Access for Your Regular User

Now that we have a regular user for daily use, we need to make sure we can SSH into the account directly.

Note: Until verifying that you can log in and use sudo with your new user, we recommend staying logged in as root. This way, if you have problems, you can troubleshoot and make any necessary changes as root. If you are using a DigitalOcean Droplet and experience problems with your root SSH connection, you can log into the Droplet using the DigitalOcean Console.

The process for configuring SSH access for your new user depends on whether your server's root account uses a password or SSH keys for authentication.

If the Root Account Uses Password Authentication

If you logged in to your root account using a password, then password authentication is enabled for SSH. You can SSH to your new user account by opening up a new terminal session and using SSH with your new username:

```cmd

ssh sammy@your_server_ip

```

After entering your regular user's password, you will be logged in. Remember, if you need to run a command with administrative privileges, type sudo before it like this:

```cmd

sudo command_to_run

```

You will be prompted for your regular user password when using sudo for the first time each session (and periodically afterwards).

To enhance your server's security, we strongly recommend setting up SSH keys instead of using password authentication. Follow our guide on setting up SSH keys on Ubuntu 18.04 to learn how to configure key-based authentication.

If the Root Account Uses SSH Key Authentication

If you logged in to your root account using SSH keys, then password authentication is disabled for SSH. You will need to add a copy of your local public key to the new user's ~/.ssh/authorized_keys file to log in successfully.

Since your public key is already in the root account's ~/.ssh/authorized_keys file on the server, we can copy that file and directory structure to our new user account in our existing session.

The simplest way to copy the files with the correct ownership and permissions is with the rsync command. This will copy the root user's .ssh directory, preserve the permissions, and modify the file owners, all in a single command. Make sure to change the highlighted portions of the command below to match your regular user's name:

Note: The rsync command treats sources and destinations that end with a trailing slash differently than those without a trailing slash. When using rsync below, be sure that the source directory (~/.ssh) does not include a trailing slash (check to make sure you are not using ~/.ssh/).

If you accidentally add a trailing slash to the command, rsync will copy the contents of the root account's ~/.ssh directory to the sudo user's home directory instead of copying the entire ~/.ssh directory structure. The files will be in the wrong location and SSH will not be able to find and use them.

```cmd

rsync --archive --chown=sammy:sammy ~/.ssh /home/sammy

```

Now, open up a new terminal session and using SSH with your new username:

```cmd

ssh sammy@your_server_ip

```

You should be logged in to the new user account without using a password. Remember, if you need to run a command with administrative privileges, type sudo before it like this:

sudo command_to_run
You will be prompted for your regular user password when using sudo for the first time each session (and periodically afterwards).


# fio 


```cmd

sudo apt install fio


```

Sequential READ speed with big blocks (this should be near the number you see in the specifications for your drive):

```cmd

fio --name TEST --eta-newline=5s --filename=fio-tempfile.dat --rw=read --size=500m --io_size=10g --blocksize=1024k --ioengine=libaio --fsync=10000 --iodepth=32 --direct=1 --numjobs=1 --runtime=60 --group_reporting

```

Sequential WRITE speed with big blocks (this should be near the number you see in the specifications for your drive):

```cmd

fio --name TEST --eta-newline=5s --filename=fio-tempfile.dat --rw=write --size=500m --io_size=10g --blocksize=1024k --ioengine=libaio --fsync=10000 --iodepth=32 --direct=1 --numjobs=1 --runtime=60 --group_reporting

```

Random 4K read QD1 (this is the number that really matters for real world performance unless you know better for sure):

```cmd

fio --name TEST --eta-newline=5s --filename=fio-tempfile.dat --rw=randread --size=500m --io_size=10g --blocksize=4k --ioengine=libaio --fsync=1 --iodepth=1 --direct=1 --numjobs=1 --runtime=60 --group_reporting

```

Mixed random 4K read and write QD1 with sync (this is worst case number you should ever expect from your drive, usually 1-10% of the number listed in the spec sheet):

```cmd

fio --name TEST --eta-newline=5s --filename=fio-tempfile.dat --rw=randrw --size=500m --io_size=10g --blocksize=4k --ioengine=libaio --fsync=1 --iodepth=1 --direct=1 --numjobs=1 --runtime=60 --group_reporting

```

Increase the --size argument to increase the file size. Using bigger files may reduce the numbers you get 

__Remember to Remove test file__

# topio

```cmd

sudo apt install topio

```

