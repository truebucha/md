# How to debug

1 Run debug build of the App

2 Attach to process by name

3 Receive the notification

4 Process should be attached now

# How to watch logs

1 Use console app for the mobile

2 
```
// To debug the extension replace `false` with true
// Go to Console App and connect to mobile device
// Filter by "NotificationService" in Subsystem or "NotificationService" in Category
#if true
import os.log
let log: (String) -> Void = {
    os_log(
        "%{public}@",
        log: OSLog(subsystem: "com.coherentsolutions.truu.ai.NotificationService", category: "NotificationService"),
        type: OSLogType.error,
        $0
    )
}
#else
let log: (String) -> Void = { _ in }
#endif
```
