
# linux exfat support

```cmd
sudo apt-get install exfat-utils exfat-fuse
```

# bluetooth mouse

1 disable iwlwifi

sudo tee /etc/modprobe.d/iwlwifi-opt.conf <<< "options iwlwifi bt_coex_active=0"

2 pair bluetooth mouse and make trusted

http://askubuntu.com/questions/663500/ubuntu-14-04-bluetooth-mouse-lags-time-by-time

Ui version

Install blueman in software center

Using it indicator pair a device

Open menu and Select devices

Find device and make it trusted by tapping gold star

Hide standard bluetooth icon by removing

```cmd
/etc/xdg/autostart/indicator-bluetooth.desktop
```

Or just pair trusted in terminal

Make sure you unpair and disconnect your mouse completely

Set   device in Pair m
Open   Terminal and

```cmd
hcitool scan
```

Make   note of the Mac address of your device in the format of   XX:XX:XX:XX
Next,   ent

```cmd
sudo bluez-simple-agent hci0 XX:XX:XX:XX:XX:XX
sudo bluez-test-device trusted XX:XX:XX:XX:XX:XX yes
sudo bluez-test-input connect XX:XX:XX:XX:XX:XX
```
After   this you can restart bluetooth service, sleep the laptop, turn off   and turn on the mouse to

# align partition

```cmd
Sudo parted check-align optimal 1
```

Create partition with offset 1MiB for 4096 kBit cluster and 2MiB for 8192

http://rainbow.chard.org/2013/01/30/how-to-align-partitions-for-best-performance-using-parted/

http://h20564.www2.hpe.com/hpsc/doc/public/display?docId=emr_na-c03479326&DocLang=en&docLocale=en_US&jumpid=reg_r11944_uken_c-001_title_r0001

```cmd
cat /sys/block/sdb/queue/optimal_io_size

  1048576

cat /sys/block/sdb/queue/minimum_io_size

  262144

cat /sys/block/sdb/alignment_offset

  0

cat /sys/block/sdb/queue/physical_block_size

  512
```
Add optimal_io_size to alignment_offset and divide the result by physical_block_size. In my case this was (1048576 + 0) / 512 = 2048.
This number is the sector at which the partition should start. Your new parted command should look like
```cmd
mkpart primary 2048s 100%
```
# groups 

Default groups; say for user123, on fresh install - (use command groups in a terminal):

user123 adm cdrom sudo dip plugdev lpadmin sambashare

Gives diff from 11.04 as

  admin is replaced by sudo
  dialout is removed
  dip is added.

To get/view defaults. Would probably work for various others too; do:

```cmd
sudo grep user-setup /var/log/installer/syslog
```

# linux ubuntu change mmc partiotions limit

[source](http://unix.stackexchange.com/questions/250347/change-the-parameters-a-kernel-module-loads-with)


When modules are loaded automatically, this is performed by the modprobe program. It reads configuration files in /etc/modprobe.d (older versions only read /etc/modprobe.conf). Create a file /etc/modprobe.d/local.conf and add the line

options mmc_block mmcblk.perdev_minors=16

http://www.howtogeek.com/howto/ubuntu/how-to-customize-your-ubuntu-kernel/

http://ubuntuforums.org/archive/index.php/t-2291447.html

```cmd
cd /usr/src

bunzip2 linux-source-2.6.17.tar.bz2

tar xvf linux-source-2.6.17.tar

ln -s linux-source-2.6.17 linux

cp /boot/config-uname -r /usr/src/linux/.config

cd /usr/src/linux

make menuconfig
```

Device Drivers -> MMC/SD/SDIO card support -> Number of minors per block device

```cmd
make-kpkg clean

fakeroot make-kpkg –initrd –append-to-version=-custom kernel_image kernel_headers

dpkg -i linux-image-2.6.17.14-ubuntu1-custom_2.6.17.14-ubuntu1-custom-10.00.Custom_i386.deb

dpkg -i linux-headers-2.6.17.14-ubuntu1-custom_2.6.17.14-ubuntu1-custom-10.00.Custom_i386.deb
```