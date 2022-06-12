# Identifiers for the apps

It looks like indentifier should be created only for the host app,
and that identifier must have all capabilities that used by an App and it's Extensions.

# Standalone Watch App

first create an bundle identifier from the Developer portal let say (com.myapp.watch)

Then your bundle ID for your targets should be as follows:

* MyApp (com.myname.myapp)
* MyApp WatchkKit App (com.myname.myapp.watchkitapp)
* MyApp WatchkKit Extension (com.myname.myapp.watchkitapp.watchkitextension)

# iOS app with extensions

* iPhone app bundle ID: com.myname.myapp
* Watch app bundle ID: com.myname.myapp.watchkitapp
* Watch extension bundle ID: com.myname.myapp.watchkitapp.watchkitextension
