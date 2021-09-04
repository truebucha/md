# MySQL

# Install

```
sudo apt install mysql-server
sudo mysql_secure_installation
configure the VALIDATE PASSWORD PLUGIN ? -> NO
set the password for root here -> Pass
all other options -> YES 
```

# Enable pasword access for root

* `sudo mysql`

* `SELECT user,authentication_string,plugin,host FROM mysql.user;`

* `ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'your new password';`

* `FLUSH PRIVILEGES;`

# Reconfigure

```
dpkg --get-selections | grep sql
sudo dpkg-reconfigure mysql-server-5.5
```

## Create User and Database

```
mysql -u root -p
CREATE DATABASE databasename;
GRANT ALL PRIVILEGES ON databasename.* TO 'UserName'@'localhost' IDENTIFIED BY 'User Password';
FLUSH PRIVILEGES;
```

`CREATE USER 'test'@'localhost' IDENTIFIED BY 'User Password'`
