<https://developer.apple.com/documentation/servicemanagement/1431078-smjobbless>

1. Add Copy File build phase, Destination: Wrapper, Subpath: Contents/Library/LaunchServices, Codesign on Copy:Disable.

2. Modify Info.plist for Both target:

  2.1 Add "Tools owned after installation" in App's Info.plist, value is: identifier "<helper's bundle identifier>" and anchor apple generic and certificate leaf[subject.CN] = "<Certificate Name>" and certificate 1[field.1.2.840.113635.100.6.2.1] /* exists */

  2.2 Add "Clients allowed to add and remove tool" in Helper's Info.plist, it is a array, so item 0's value is: identifier "<app's bundle identifier>" and anchor apple generic and certificate leaf[subject.CN] = "<Certificate Name>" and certificate 1[field.1.2.840.113635.100.6.2.1] /* exists */

  2.3 Make sure each .plist file is set as Info.plist in Target's Build settings.

3. Choose Developer ID:* in Code Signing Identity in build settings for each targets.

4. Build app.

5. Use "SMJobBlessUtil.py" in SMJobBless project.

  5.1 Update Info.plist:

  Format: $ ./SMJobBlessUtil.py setreq <App path> <App's Info.plist path> <Helper's Info.plist>

  Example: $ ./SMJobBlessUtil.py setreq ~/Library/Developer/Xcode/DerivedData/Build/Products/Debug/App.app App/Info.plist Helper/Helper-Info.plist
  
  5.2 Check Code Signing status:
  
  Format: $ ./SMJobBlessUtil.py check <App path>
  
  Example: $ ./SMJobBlessUtil.py check ~/Library/Developer/Xcode/DerivedData/Build/Products/Debug/App.app
  
  If got any error, re-check step 3.
  
6. Use "SMJobKit" code to install helper. No need to import its framework, just use files in SMJobKit folder.
