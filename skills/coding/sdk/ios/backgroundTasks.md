## <https://developer.apple.com/documentation/backgroundtasks/starting_and_terminating_tasks_during_development>

### To launch a task:

* Set a breakpoint in the code that executes after a successful call to submit(_:).
* Run your app on a device until the breakpoint pauses your app.
* In the debugger, execute the line shown below, substituting the identifier of the desired task for TASK_IDENTIFIER.
* Resume your app. The system calls the launch handler for the desired task.

`e -l objc -- (void)[[BGTaskScheduler sharedScheduler] _simulateLaunchForTaskWithIdentifier:@"TASK_IDENTIFIER"]`

### Force Early Termination of a Task

* Set a breakpoint in the desired task.
* Launch the task using the debugger as described in the previous section.
* Wait for your app to pause at the breakpoint.
* In the debugger, execute the line shown below, substituting the identifier of the desired task for TASK_IDENTIFIER.
* Resume your app. The system calls the expiration handler for the desired task.

`e -l objc -- (void)[[BGTaskScheduler sharedScheduler] _simulateExpirationForTaskWithIdentifier:@"TASK_IDENTIFIER"]`
