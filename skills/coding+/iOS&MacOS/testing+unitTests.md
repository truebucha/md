
# test push notifications on simulator

`xcrun simctl list`

`xcrun simctl push A667FF9A-8C03-4AEA-838C-FE6CEB56776F Payload.apns`

```
{
    "aps": {
        "alert": {
            "body": "Test message",
            "title": "Optional title",
            "subtitle": "Optional subtitle"
        },
        "sound": "default",
        "category": "Info_Push",
        "thread-id": "5281"
    },
    "Simulator Target Bundle": "group.detecta.apps.connect"
}

```


# Quick + Nible

[Ray writo a really good article about it](https://www.raywenderlich.com/135-behavior-driven-testing-tutorial-for-ios-with-quick-nimble)

```
describe JukeBox do
  describe ‘.play’ do
    context 'when user has inserted coin' do
      it 'return song being played message' do
      end
    end
    context 'when user has not inserted coin' do
      it 'return insert coin message' do
      end
    end
  end
end
```

# testing share ext

* add NSLog and use the Console.app to see the device logs.

* use debug on device 

```
* Run your app
* While the app is running, go to xCode -> Debug -> Attach to process by PID or name
* Write the name or bundle id of your extension and click attach (app-share-extension)
* Then run your extension with any way you can do this on your device.
* Wait for debugger to stop the extension at breakpoint.
```
