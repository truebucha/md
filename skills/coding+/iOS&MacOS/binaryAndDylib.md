
# Check binary

* `otool -L Binary`

```
@rpath/libswift_Concurrency.dylib (compatibility version 1.0.0, current version 5.6.0, weak)
```

* `otool -l Binary`

```
load command 45
          cmd LC_LOAD_WEAK_DYLIB
      cmdsize 64
         name @rpath/libswift_Concurrency.dylib (offset 24)
   time stamp 2 Thu Jan  1 01:00:02 1970
      current version 5.6.0
compatibility version 1.0.0
Load command 46
          cmd LC_RPATH
      cmdsize 32
         path /usr/lib/swift (offset 12)
Load command 47
          cmd LC_RPATH
      cmdsize 48
         path @executable_path/../Frameworks (offset 12)
```

# Check dylib

* `dyld_info libswift_Concurrency.dylib`

# Check runtime 

* in the debugger console, if you run `image list`

# Check all loaded libraries in the system

`DYLD_PRINT_LIBRARIES=YES /usr/bin/true`


