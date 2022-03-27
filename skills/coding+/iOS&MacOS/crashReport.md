

# PLCrashReporter - best way to handle low level crashes


# symbolicate

<https://developer.apple.com/documentation/xcode/diagnosing_issues_using_crash_reports_and_device_logs>

<https://developer.apple.com/documentation/xcode/diagnosing_issues_using_crash_reports_and_device_logs/adding_identifiable_symbol_names_to_a_crash_report#3403795>

```
atos -arch <BinaryArchitecture> -o <PathToDSYMFile>/Contents/Resources/DWARF/<BinaryName>  -l <LoadAddress> <AddressesToSymbolicate>

atos -arch arm64 -o TouchCanvas.app.dSYM/Contents/Resources/DWARF/TouchCanvas -l 0x1022c0000 0x00000001022df754

```

```
mdfind "com_apple_xcode_dsym_uuids == C61D1B3F-6B63-3050-AF7E-55E2C6290163"

dwarfdump --uuid <PathToDSYMFile>/Contents/Resources/DWARF/<BinaryName>

dwarfdump --uuid <PathToDSYMFile>/Contents/Resources/DWARF/<BinaryName>

dwarfdump --uuid <PathToBinary>

dsymutil -symbol-map <PathToXcodeArchive>/MyGreatApp.xcarchive/BCSymbolMaps <PathToDownloadedDSYMs>/<UUID>.dSYM

```



