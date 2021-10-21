# validation tool

* <https://search.developer.apple.com/appsearch-validation-tool/>
* <https://www.appsflyer.com/tools/app-links-validator/>

# Server side

https://search.developer.apple.com/appsearch-validation-tool/

To use `applinks:*.mydomain.com` you need to have the association file also be served from the domain without the wildcard.

So, using my example above,
the association file also needs to be available from https://mydomain.com as well as https://username.mydomain.com.

**the file:** `mydomain.com/.well-known/apple-app-site-association`

data: **teamId**: 4D96X2TNB8; **bundleId**: com.coherentsolutions.truu.ai

contents: `{"applinks": {"apps": [], "details": [{"appID": "4D96X2TNB8.com.coherentsolutions.truu.ai", "paths": ["*"]}]}}`

## check here



# mobile side 

`applinks:*.mydomain.com`
