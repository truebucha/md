# Sugestions 

* используй метод локи для управления памятью

# Connect to VPN first time

## download client from <https://vpn-by.coherentsolutions.com> 

https://vpn-by.coherentsolutions.com/+CSCOE+/noportal.html

## connect to url `vpn-by.coherentsolutions.com`

## use domain login without @ part

or create `.anyconnect` file in the user directory
```
<?xml version="1.0" encoding="UTF-8"?>
<AnyConnectPreferences>
<DefaultUser>konstantinbucha</DefaultUser>
<DefaultSecondUser></DefaultSecondUser>
<ClientCertificateThumbprint>F3FD653A7EE0E9613BE1BCB9C774EA24AF424DDC</ClientCertificateThumbprint>
<MultipleClientCertificateThumbprints></MultipleClientCertificateThumbprints>
<ServerCertificateThumbprint></ServerCertificateThumbprint>
<DefaultHostName>vpn-by.coherentsolutions.com</DefaultHostName>
<DefaultHostAddress></DefaultHostAddress>
<DefaultGroup>1-ISSoft-VPN</DefaultGroup>
<ProxyHost></ProxyHost>
<ProxyPort></ProxyPort>
<SDITokenType>none</SDITokenType>
<ControllablePreferences></ControllablePreferences>
</AnyConnectPreferences>
```

# Slack 

## Build for the TruU test flight

`/ios-truu stage_appstore WA-5704 21.88.0`

# Protobuf

### [swift-protobuf](https://github.com/apple/swift-protobuf)

### brew install

```
brew install swift-protobuf
```

### generate from proto file 

```
protoc --swift_out=. --swift_opt=Visibility=Public TruUTransmitData.proto
```

[options](https://github.com/apple/swift-protobuf/blob/master/Documentation/PLUGIN.md#generation-option-visibility---visibility-of-generated-types)


# Cloud Platform

## Test users

dariyayuchas Sedriya26 

* cloud_stage | konstantinb | Passwd_9

* cloud_qa | konstantinb | Passwd_9

* cloud_stage | konstantinbucha | Hello123!!

* cloud_qa | konstantinbucha | Hello123!!

### stage mail <http://mail.coh-test.xyz/mail>

ivany@coh-test.xyz

Passwd_26

localhost

## STAGE 

* Cloud Console <https://coherenttest.stage.truu.ai/>

* Cloud domain name `coh-test.xyz`

* Identity Server `cloud.coh-test.xyz`

* DomainID 9dfb3c2d-bdbf-48f0-b9ea-c83729e29f21


## QA

* Cloud Console <https://qa-coherent.qa.truu.ai/>

* Cloud domain name `coh-qa.xyz`

* Identity Server `cloud.coh-qa.xyz`

* DomainID 15d34d67-388e-4f40-8917-c2c3712f09e8 

# add PC to domain

<https://truudev.atlassian.net/wiki/spaces/WA/pages/541655192/Cloud+Configuration+Instructions>

pfx cert pass: Hello123!!

domain coh-test.xyz

konstantinbucha @coh-test.xyz @coh-qa.xyzдля стэйджа и для qa соответственно пароль Hello123!!

# company holidays

01/01/2021	Friday	New Year's Holiday

01/07/2021	Thursday	Orthodox Christmas

01/08/2021	Friday	Company Holiday

03/08/2021	Monday	Women's Day

05/10/2021	Monday	Company Holiday

05/11/2021	Tuesday	Radunitsa

12/31/2021	Friday	Company Holiday

# Win Agent 

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


### rssi same for both modes

### background mode `overflow area`

`dataSect: 255, hex: 4C-00-01-04-00-00-00-00-20-00-00-40-00-40-20-00-00-01-00;`

2021-01-05 19:42:49.0278|INFO|21|TruUAgentService.RssiFilter.LogRSSI|[Recieved] addr: 133657669727376: uuid: 00000000-0000-0000-0000-000000000000, rssi: -37, TxPower: , Distance: 0.0707945784384138. AdvType: ScanResponse. LocalName: . iOSManData.Cnt: 1. iOSManData: System.__ComObject. DataSections.Cnt: 1. dataSect: 255, hex: 4C-00-01-04-00-00-00-00-20-00-00-40-00-40-20-00-00-01-00; ComId: 76, hex: 01-04-00-00-00-00-20-00-00-40-00-40-20-00-00-01-00; ||

### foreground mode

2021-01-05 19:45:59.1105|INFO|26|TruUAgentService.RssiFilter.LogRSSI|[Recieved] addr: 133657669727376: uuid: 00000000-0000-0000-0000-000000000000, rssi: -42, TxPower: , Distance: 0.125892541179417. AdvType: ScanResponse. LocalName: . iOSManData.Cnt: 1. iOSManData: System.__ComObject. DataSections.Cnt: 1. dataSect: 255, hex: 4C-00-01-04-00-00-00-00-20-00-00-40-00-40-20-00-00-01-00; ComId: 76, hex: 01-04-00-00-00-00-20-00-00-40-00-40-20-00-00-01-00; ||


### initiate command session from WA

login into user

in command prompt type certutil -scinfo

# Desktop Agent Token Request

eyJ2ZXIiOiIyLjAiLCJ0eXAiOiJKV1QiLCJhbGciOiJFUzM4NCIsImtpZCI6Ijc4ZGVlNmViZGY5NDRhZDE4NzZhNWJiMWVmZTA3MzgyIn0.eyJzdWIiOiJhY2E2ODcwZi0yM2IxLTQ4MjgtOWU4My01ZDU0MTQ0NzM3Y2QiLCJzY29wZSI6WyJkZXNrdG9wLWFnZW50Il0sImRvbWFpbiI6IjE1ZDM0ZDY3LTM4OGUtNGY0MC04OTE3LWMyYzM3MTJmMDllOCIsImlzcyI6Imh0dHBzOlwvXC9xYS5wbGF0Zm9ybS50cnV1LmFpIiwiZXhwIjoxNjE4NDkyMzU4LCJpYXQiOjE2MTg0MDU5NTgsIm5vbmNlIjoicEdnYlM3eW5FV3BYQ051VE5RLXhHQjkyWVVHN1V3NVR0RE92XzBUclduZyIsImp0aSI6IjQxMDAwY2JmLWRlYWQtNGFlNC05YzMyLTNmMDZjZDM0ZjIwZCJ9.WBp10HQTEmu42ubdk1U6Dxi82t1nUUm4vcDO_PzxZRKwV6SLu4IpFWc0CMmeEadvc6zvqLGQnNcl9LNMKk2SDxpvKlY5hGpASIbiWV2e07oa952iR8usFYc8zAkOI1qA

client_id: aca6870f-23b1-4828-9e83-5d54144737cd
client_secret: Hello123!!
scope: desktop-agent
