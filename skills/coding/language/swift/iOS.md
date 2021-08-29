## Point free

- [ ] <https://www.pointfree.co/episodes/ep154-async-refreshable-composable-architecture>




### run runloop and register a n AppDelegate

let kIsRunningTests = NSClassFromString("XCTestCase") != nil
let kAppDelegateClass = kIsRunningTests ? nil : NSStringFromClass(AppDelegate.self)

UIApplicationMain(CommandLine.argc, CommandLine.unsafeArgv, nil, kAppDelegateClass)
