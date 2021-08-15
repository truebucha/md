### registry settigns 

`Registry Editor`

`Computer\HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Authentication\Credential Providers\{5fd3d285-0dd9-4362-8855-e0abaacd4af6}`

`enhancedRSSILogging` 1

### restart service

`Services`

`TruUService` -> Restart

### logs

`C:\Program Files\TruU Inc\logs`

`rssi.log`


# rssi same for both modes

### background mode `overflow area`

`dataSect: 255, hex: 4C-00-01-04-00-00-00-00-20-00-00-40-00-40-20-00-00-01-00;`

2021-01-05 19:42:49.0278|INFO|21|TruUAgentService.RssiFilter.LogRSSI|[Recieved] addr: 133657669727376: uuid: 00000000-0000-0000-0000-000000000000, rssi: -37, TxPower: , Distance: 0.0707945784384138. AdvType: ScanResponse. LocalName: . iOSManData.Cnt: 1. iOSManData: System.__ComObject. DataSections.Cnt: 1. dataSect: 255, hex: 4C-00-01-04-00-00-00-00-20-00-00-40-00-40-20-00-00-01-00; ComId: 76, hex: 01-04-00-00-00-00-20-00-00-40-00-40-20-00-00-01-00; ||

### foreground mode

2021-01-05 19:45:59.1105|INFO|26|TruUAgentService.RssiFilter.LogRSSI|[Recieved] addr: 133657669727376: uuid: 00000000-0000-0000-0000-000000000000, rssi: -42, TxPower: , Distance: 0.125892541179417. AdvType: ScanResponse. LocalName: . iOSManData.Cnt: 1. iOSManData: System.__ComObject. DataSections.Cnt: 1. dataSect: 255, hex: 4C-00-01-04-00-00-00-00-20-00-00-40-00-40-20-00-00-01-00; ComId: 76, hex: 01-04-00-00-00-00-20-00-00-40-00-40-20-00-00-01-00; ||


# initiate command session from WA

login into user

in command prompt type certutil -scinfo
