# WrodPress

## Config

<https://api.wordpress.org/secret-key/1.1/salt/>

```
/* Add this line to allow direct modification of files (install updates, themes etc.) The owner should be www-data:root where www-data is php-fpm user
define( 'FS_METHOD', 'direct' );
```
