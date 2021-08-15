
# [Official Site](https://www.raspberrypi.org)

[download drive image](https://www.raspberrypi.org/downloads/)

[rufus tool to - burn image to flash -](https://rufus.akeo.ie/)

# How To [Guide](r-raspberryPi/RaspberryPi.html)

# Config 

config.txt file on first drive on the flash

used to set up device cpu perfomance

* [for graphic perfomance](r-raspberryPi/config_05_17_force_turbo.txt)

> to use cma add this to cmdline.txt "coherent_pool=6M smsc95xx.turbo_mode=N"


* [for server mode perfomance](r-raspberryPi/config_10_01_18.txt)

# Local Blynk Server

[github repo](https://github.com/blynkkk/blynk-server)

Install

Login to Raspberry Pi via ssh:

Install java 8:

```cmd
  sudo apt-get install oracle-java8-jdk
```

Make sure you are using Java 8

```cmd
  java -version
  Output: java version "1.8"
```

Download Blynk server jar file (or manually copy it to Raspberry Pi via ssh and scp command):

```cmd
  wget "https://github.com/blynkkk/blynk-server/releases/download/v0.39.5/server-0.39.5-java8.jar"
```

Run the server on default 'hardware port 8080' and default 'application port 9443' (SSL port)

```cmd
  java -jar server-0.39.5-java8.jar -dataFolder /home/pi/Blynk
```

That's it!

As output you will see something like that:

```cmd
  Blynk Server successfully started.
  All server output is stored in current folder in 'logs/blynk.log' file.
```

# GPIO libs

[(that is fastest one)](http://elinux.org/RPi_GPIO_Code_Samples#bcm2835_library)

[mkaczanowski/BeagleBoneBlack-GPIO](https://github.com/mkaczanowski/BeagleBoneBlack-GPIO)
Simple C++ library that handles GPIO calls for BeagleBone Black - 

[JamesBarwell/rpi-gpio.js](https://github.com/JamesBarwell/rpi-gpio.js)
Control Raspberry Pi GPIO pins with node.js. Contribute to JamesBarwell/rpi-gpio.js development by creating an account on GitHub.

[jperkin/node-rpio](https://github.com/jperkin/node-rpio)
Raspberry Pi GPIO library for node.js. Contribute to jperkin/node-rpio development by creating an account on GitHub.

[akira-cn/rpio2](https://github.com/akira-cn/rpio2)
Control Raspberry Pi GPIO pins with node.js. Fast and easy to use. - akira-cn/rpio2 
