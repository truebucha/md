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

* `ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'password';`

## Create User

* `mysql -u root -p`

*
