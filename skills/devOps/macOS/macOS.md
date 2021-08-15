
# use pbcopy & pbpaste

```cmd 

$ ps aux | pbcopy

pbpaste > pf.rules

```


# setup proxy 

Use `networksetup` and `ifconfig`

```cmd

networksetup -listallnetworkservices

networksetup -listallhardwareports

networksetup -getinfo iPhone\ USB

networksetup -setwebproxy iPhone\ USB 169.254.118.67 8888

networksetup  -getwebproxy iPhone\ USB ::1 8888

networksetup -getwebproxy iPhone\ USB

networksetup -setwebproxystate iPhone\ USB on

networksetup -getsecurewebproxy iPhone\ USB

networksetup -setsecurewebproxy iPhone\ USB ::1 8888

Usage: networksetup -setsecurewebproxystate iPhone\ USB on


```

```cmd

echo "
rdr pass inet proto tcp from any to any port 80 -> 127.0.0.1 port 8080
" | sudo pfctl -ef -

rdr pass on bridge100 inet proto tcp from any to any -> 127.0.0.1 port 8080 

https://apple.stackexchange.com/questions/230300/what-is-the-modern-way-to-do-port-forwarding-on-el-capitan-forward-port-80-to

https://gist.github.com/novemberborn/aea3ea5bac3652a1df6b

```


/etc/pf.conf

```
#
# com.apple anchor point
#
scrub-anchor "com.apple/*"
nat-anchor "com.apple/*
#nat-anchor "ios"
rdr-anchor "com.apple/*"
#rdr-anchor "ios"
dummynet-anchor "com.apple/*"
anchor "com.apple/*"
load anchor "com.apple" from "/etc/pf.anchors/com.apple"
#load anchor "ios" from "/etc/pf.anchors/ios"
```


/etc/pf.anchors/ios

```

nat on vmnet8 from bridge100:network to any -> (vmnet8)
rdr pass on bridge100 inet proto tcp from any to any port 80 -> 127.0.0.1 port 8888
rdr pass on bridge100 inet proto tcp from any to any port 443 -> 127.0.0.1 port 8888

```

sudo pfctl -ef /etc/pf.conf


# apps

### vpn & proxy

charles, windscribe

### raster editor

Seashore - free image editor for developers

### vector design tool

inVision Studio, Adobe XD, Sketch

### iOS tool 

iFunbox, SimSim

## status bar timer

Horo

## sql database reader

Datum Free, RazorSQL

## boot media creator

Etcher

## ftp client

FileZilla

## music

Garage Band,

## git viewers

Fork, Source Tree

