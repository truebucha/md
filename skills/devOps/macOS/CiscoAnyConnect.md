To reinstall use

sudo pkgutil --forget com.cisco.pkg.anyconnect.vpn

To remove 

sudo /opt/cisco/anyconnect/bin/vpn_uninstall.sh

Enter these commands to clean out the old Cisco VPN kernel extension and reboot the system.

```
    sudo -s
    rm -rf /System/Library/StartupItems/CiscoVPN
    rm -rf /Library/StartupItems/CiscoVPN
    rm -rf /System/Library/Extensions/CiscoVPN.kext
    rm -rf /Library/Extensions/CiscoVPN.kext
    rm -rf /Library/Receipts/vpnclient-kext.pkg
    rm -rf /Library/Receipts/vpnclient-startup.pkg
    reboot
```   

If you installed the Cisco VPN for Mac version 4.1.08005 package, enter these commands to delete the misplaced files. The deletion of these files will not affect your system, since applications do not use these misplaced files in their current location.

```
    sudo -s
    rm -rf /Cisco\ VPN\ Client.mpkg
    rm -rf /com.nexUmoja.Shimo.plist
    rm -rf /Profiles
    rm -rf /Shimo.app
    exit
```

Enter these commands if you no longer need the old Cisco VPN Client or Shimo.

```
    sudo -s
    rm -rf /Library/Application\ Support/Shimo
    rm -rf /Library/Frameworks/cisco-vpnclient.framework
    rm -rf /Library/Extensions/tun.kext
    rm -rf /Library/Extensions/tap.kext
    rm -rf /private/opt/cisco-vpnclient
    rm -rf /Applications/VPNClient.app
    rm -rf /Applications/Shimo.app
    rm -rf /private/etc/opt/cisco-vpnclient
    rm -rf /Library/Receipts/vpnclient-api.pkg
    rm -rf /Library/Receipts/vpnclient-bin.pkg
    rm -rf /Library/Receipts/vpnclient-gui.pkg
    rm -rf /Library/Receipts/vpnclient-profiles.pkg
    rm -rf ~/Library/Preferences/com.nexUmoja.Shimo.plist
    rm -rf ~/Library/Application\ Support/Shimo
    rm -rf ~/Library/Preferences/com.cisco.VPNClient.plist
    rm -rf ~/Library/Application\ Support/SyncServices/Local/TFSM/com.
       nexumoja.Shimo.Profiles
    rm -rf ~/Library/Logs/Shimo*
    rm -rf ~/Library/Application\ Support/Shimo
    rm -rf ~/Library/Application\ Support/Growl/Tickets/Shimo.growlTicket
    exit
```    
    
Finally this.

sudo pkgutil --forget com.cisco.pkg.anyconnect.vpn
