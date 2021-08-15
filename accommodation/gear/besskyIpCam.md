

# open ports 

23 telnet

554 rtsp

5040 unknown

5050 mmcc

5051 ita-agent

8800 sunwebadmin

8899 unknown

# online description

http://www.bessky.com/product/html/289.html

# shinobi setup

cp super.sample.json super.json

Login from the main dashboard with Superuser selected.

Username : admin@shinobi.video

Password : admin

user: ccio@m03.ca

pass 131415

rtsp://192.168.100.17/live/ch00_1


https://forum.use-ip.co.uk/threads/hacking-china-ip-camera-need-help-for-rtsp-password-for-telnet.938/

config:

```javascript
{"mode":"record","mid":"mOoDeeKsym","name":"cam","type":"h264","protocol":"rtsp","host":"192.168.100.17","port":"554","path":"/live/ch00_1","ext":"mp4","fps":"1","width":"1280","height":"720","details":"{\"fatal_max\":\"\",\"notes\":\"\",\"rtsp_transport\":\"tcp\",\"muser\":\"adm\",\"mpass\":\"131415\",\"port_force\":null,\"sfps\":\"1\",\"aduration\":\"\",\"stream_type\":\"b64\",\"stream_mjpeg_clients\":\"\",\"stream_vcodec\":\"libx264\",\"stream_acodec\":\"libmp3lame\",\"hls_time\":\"2\",\"preset_stream\":\"ultrafast\",\"hls_list_size\":\"3\",\"signal_check\":\"10\",\"signal_check_log\":\"0\",\"stream_quality\":\"1\",\"stream_fps\":\"10\",\"stream_scale_x\":\"1280\",\"stream_scale_y\":\"720\",\"svf\":\"\",\"snap\":\"1\",\"snap_fps\":\"10\",\"snap_scale_x\":\"1280\",\"snap_scale_y\":\"720\",\"vcodec\":\"libx264\",\"crf\":\"1\",\"preset_record\":\"\",\"acodec\":\"libmp3lame\",\"dqf\":\"0\",\"cutoff\":\"1\",\"vf\":\"\",\"timestamp\":\"0\",\"timestamp_font\":\"\",\"timestamp_font_size\":\"10\",\"timestamp_color\":\"white\",\"timestamp_box_color\":\"0x00000000@1\",\"timestamp_x\":\"(w-tw)/2\",\"timestamp_y\":\"0\",\"cust_input\":\"\",\"cust_snap\":\"\",\"cust_detect\":\"\",\"cust_stream\":\"\",\"cust_record\":\"\",\"custom_output\":\"\",\"detector\":\"0\",\"detector_trigger\":null,\"detector_timeout\":\"\",\"watchdog_reset\":null,\"detector_save\":null,\"detector_mail\":\"0\",\"detector_mail_timeout\":\"\",\"detector_fps\":\"\",\"detector_scale_x\":\"\",\"detector_scale_y\":\"\",\"detector_frame\":\"1\",\"detector_sensitivity\":\"\",\"detector_command_enable\":null,\"detector_command\":\"\",\"detector_command_timeout\":\"\",\"cords\":\"\",\"detector_face\":null,\"detector_fullbody\":null,\"detector_car\":null,\"detector_notrigger\":null,\"detector_notrigger_mail\":null,\"detector_notrigger_timeout\":\"\",\"control\":\"0\",\"control_base_url\":\"\",\"control_stop\":\"0\",\"control_url_stop_timeout\":\"\",\"control_url_center\":\"\",\"control_url_left\":\"\",\"control_url_left_stop\":\"\",\"control_url_right\":\"\",\"control_url_right_stop\":\"\",\"control_url_up\":\"\",\"control_url_up_stop\":\"\",\"control_url_down\":\"\",\"control_url_down_stop\":\"\",\"groups\":\"[]\",\"loglevel\":\"warning\",\"sqllog\":\"0\"}","shto":"[]","shfr":"[]"}
```

# onvif v2
----

```cmd
curl  -X POST --header 'Content-Type: text/xml; charset=utf-8' -d @xmlbody.xml 'http://192.168.100.17:8899/onvif/device_service'

<s:Envelope xmlns:s="http://www.w3.org/2003/05/soap-envelope">
<s:Header>
</s:Header>
<s:Body xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema">
<GetCapabilities xmlns="http://www.onvif.org/ver10/device/wsdl">
<Category>All</Category>
</GetCapabilities>
</s:Body>
</s:Envelope>
```

response 

```xml
<?xml version="1.0" encoding="UTF-8"?>
<SOAP-ENV:Envelope xmlns:SOAP-ENV="http://www.w3.org/2003/05/soap-envelope" xmlns:SOAP-ENC="http://www.w3.org/2003/05/soap-encoding" xmlns:c14n="http://www.w3.org/2001/10/xml-exc-c14n#" xmlns:chan="http://schemas.microsoft.com/ws/2005/02/duplex" xmlns:ds="http://www.w3.org/2000/09/xmldsig#" xmlns:tds="http://www.onvif.org/ver10/device/wsdl" xmlns:tev="http://www.onvif.org/ver10/events/wsdl" xmlns:timg="http://www.onvif.org/ver20/imaging/wsdl" xmlns:tmd="http://www.onvif.org/ver10/deviceIO/wsdl" xmlns:tptz="http://www.onvif.org/ver20/ptz/wsdl" xmlns:trc="http://www.onvif.org/ver10/recording/wsdl" xmlns:trt="http://www.onvif.org/ver10/media/wsdl" xmlns:tt="http://www.onvif.org/ver10/schema" xmlns:wsa="http://schemas.xmlsoap.org/ws/2004/08/addressing" xmlns:wsa5="http://www.w3.org/2005/08/addressing" xmlns:wsc="http://schemas.xmlsoap.org/ws/2005/02/sc" xmlns:wsdd="http://schemas.xmlsoap.org/ws/2005/04/discovery" xmlns:wsnt="http://docs.oasis-open.org/wsn/b-2" xmlns:wsse="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd" xmlns:wsu="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd" xmlns:xenc="http://www.w3.org/2001/04/xmlenc#" xmlns:xmime="http://tempuri.org/xmime.xsd" xmlns:xop="http://www.w3.org/2004/08/xop/include" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
   <SOAP-ENV:Header />
   <SOAP-ENV:Body>
      <tds:GetCapabilitiesResponse>
         <tds:Capabilities>
            <tt:Device>
               <tt:XAddr>http://192.168.100.17:8899/onvif/device_service</tt:XAddr>
               <tt:Network>
                  <tt:IPFilter>false</tt:IPFilter>
                  <tt:ZeroConfiguration>false</tt:ZeroConfiguration>
                  <tt:IPVersion6>false</tt:IPVersion6>
                  <tt:DynDNS>false</tt:DynDNS>
               </tt:Network>
               <tt:System>
                  <tt:DiscoveryResolve>true</tt:DiscoveryResolve>
                  <tt:DiscoveryBye>true</tt:DiscoveryBye>
                  <tt:RemoteDiscovery>false</tt:RemoteDiscovery>
                  <tt:SystemBackup>false</tt:SystemBackup>
                  <tt:SystemLogging>false</tt:SystemLogging>
                  <tt:FirmwareUpgrade>false</tt:FirmwareUpgrade>
                  <tt:SupportedVersions>
                     <tt:Major>2</tt:Major>
                     <tt:Minor>2</tt:Minor>
                  </tt:SupportedVersions>
               </tt:System>
               <tt:IO>
                  <tt:InputConnectors>1</tt:InputConnectors>
                  <tt:RelayOutputs>1</tt:RelayOutputs>
               </tt:IO>
               <tt:Security>
                  <tt:TLS1.1>false</tt:TLS1.1>
                  <tt:TLS1.2>false</tt:TLS1.2>
                  <tt:OnboardKeyGeneration>false</tt:OnboardKeyGeneration>
                  <tt:AccessPolicyConfig>false</tt:AccessPolicyConfig>
                  <tt:X.509Token>false</tt:X.509Token>
                  <tt:SAMLToken>false</tt:SAMLToken>
                  <tt:KerberosToken>false</tt:KerberosToken>
                  <tt:RELToken>false</tt:RELToken>
               </tt:Security>
            </tt:Device>
            <tt:Media>
               <tt:XAddr>http://192.168.100.17:8899/onvif/Media</tt:XAddr>
               <tt:StreamingCapabilities>
                  <tt:RTPMulticast>true</tt:RTPMulticast>
                  <tt:RTP_TCP>true</tt:RTP_TCP>
                  <tt:RTP_RTSP_TCP>true</tt:RTP_RTSP_TCP>
               </tt:StreamingCapabilities>
            </tt:Media>
            <tt:PTZ>
               <tt:XAddr>http://192.168.100.17:8899/onvif/PTZ</tt:XAddr>
            </tt:PTZ>
            <tt:Extension>
               <tt:DeviceIO>
                  <tt:XAddr>http://192.168.100.17:8899/onvif/DeviceIO</tt:XAddr>
                  <tt:VideoSources>1</tt:VideoSources>
                  <tt:VideoOutputs>0</tt:VideoOutputs>
                  <tt:AudioSources>0</tt:AudioSources>
                  <tt:AudioOutputs>0</tt:AudioOutputs>
                  <tt:RelayOutputs>1</tt:RelayOutputs>
               </tt:DeviceIO>
            </tt:Extension>
         </tds:Capabilities>
      </tds:GetCapabilitiesResponse>
   </SOAP-ENV:Body>
</SOAP-ENV:Envelope>
```