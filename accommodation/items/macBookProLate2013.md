# usb charging cycling on/off for iphone

* solution: I was able to fix the issue by restarting the USB service.

```
sudo killall -STOP -c usbd
```
