### Stage: Kibana: Elastic search logs 

https://nam02.safelinks.protection.outlook.com/?url=https%3A%2F%2Fcoh.logs.internal.truu.ai%2F_plugin%2Fkibana%2Fapp%2Fdiscover&data=04%7C01%7CAlexeyBarantsevich%40coherentsolutions.com%7C010451154a0f4404e3e808d8dce86a1c%7C81915a7774c44370a6f97e5e66322233%7C0%7C0%7C637502238078679308%7CUnknown%7CTWFpbGZsb3d8eyJWIjoiMC4wLjAwMDAiLCJQIjoiV2luMzIiLCJBTiI6Ik1haWwiLCJXVCI6Mn0%3D%7C1000&sdata=jTL0pxVwWN6BO1OhhVWBZXI%2FN%2BK%2B%2F3Vc6Lta%2F%2BYfLhw%3D&reserved=0

https://coh.logs.internal.truu.ai/_plugin/kibana/app/discover#/


### Connect to Cloud QA via ssh

* connect Azure VPN

* connect via terminal, pass in 1password "cloud qa identity server"

```
ssh truu-admin@10.0.0.5

tail -f /opt/truu/ids/ids.log | grep 'Endpoint\|Handler'
```

this one will rewrite a file on start

```
ssh truu-admin@10.0.0.5 "tail -f /opt/truu/ids/ids.log" > 1.log
```

this one will append to a file on start

```
ssh truu-admin@10.0.0.5 "tail -f /opt/truu/ids/ids.log" >> 1.log
```

```
c.truu.id.server.ws.EndpointController processing endpoint requests
c.t.i.s.i.EndpointIdentityProcessorImpl starting request sessions
c.t.i.s.e.h.AnonymousIdentityHandler  routing messages
com.truu.core.ws.SubscriptionHandler - processing frames

'Endpoint\|Handler'
```
