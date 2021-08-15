First, you need to log into recovery mode and turn off SPI via terminal: csrutil disable

then remove all pathes from 

/Applications/Symantec Solutions

/Library/Application Support/Symantec

/Library/Services

/private/etc/symantec

/usr/local/lib/libecomlodr.dylib

/Library/LaunchAgents/com.symantec.uiagent.application.MES.plist

/Library/System Extensions/  find one for symantec and delete only it or use

systemextensionsctl list from terminal.  Use the list parameter and then the uninstall one with the parameters retrieved from running it with list.  
Looked like this on my system: systemextensionsctl uninstall 9PTGMPNXZ2 com.symantec.mes.systemextension;

launchctl list
launchctl remove com.symantec.uiagent.application.MES.plist

Then, back into recovery mode to turn SPI back on and run csrutil enable
