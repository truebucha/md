
# iOS, Mac coding

## Good Sources

* <https://github.com/apple-oss-distributions>

## Swift best practices

* [be-careful-using-dispatchgroups-with-fast-running-code](https://medium.com/@joesusnick/be-careful-using-dispatchgroups-with-fast-running-code-98ecdc08beb3)

* [Swift restricted import](https://nshipster.com/import/)


## Acessability

* [supporting_voiceover_in_your_app](https://developer.apple.com/documentation/uikit/accessibility/supporting_voiceover_in_your_app)

* [accessibilityTraits](https://developer.apple.com/documentation/uikit/accessibility/uiaccessibility#//apple_ref/occ/instp/NSObject/accessibilityTraits)

```swift 

score.isAccessibilityElement = true
score.accessibilityLabel = "score: \(currentScore)"
score.accessibilityHint = "Your current score" 

var elements = [UIAccessibilityElement]()
let groupedElement = UIAccessibilityElement(accessibilityContainer: self)
groupedElement.accessibilityLabel = "\(nameTitle.text!), \(nameValue.text!)"
groupedElement.accessibilityFrameInContainerSpace = nameTitle.frame.union(nameValue.frame)
elements.append(groupedElement)

```

# xcode 

##  DeviceSupport

```cmd 

cd /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/DeviceSupport

```

[https://github.com/iGhibli/iOS-DeviceSupport/tree/master/DeviceSupport](https://github.com/iGhibli/iOS-DeviceSupport/tree/master/DeviceSupport)

## Sotp tracking workspace config 

```cmd

git update-index --assume-unchanged 

```

# documents 

[clang.llvm.org](http://clang.llvm.org/docs/AutomaticReferenceCounting.html#retained-return-values)


# Simulator

[command line](https://medium.com/@ankitkumargupta/ios-simulator-command-line-tricks-ee58054d30f4)

in case build problems in xcode 

```
sudo killall -9 com.apple.CoreSimulator.CoreSimulatorService
```

# Swift 

## swift in the frameworks

### import swift file in objc 

[link](https://developer.apple.com/documentation/swift/imported_c_and_objective-c_apis/importing_swift_into_objective-c)

```
#import <ProductName/ProductModuleName-Swift.h>
```

## links

### style guide

[style guide  by Ray](https://github.com/raywenderlich/swift-style-guide)

# links 

[bignerdranch](https://www.bignerdranch.com/blog/categories/ios/)

[nshipster](http://nshipster.com/)

[ray](https://www.raywenderlich.com/)

# frameworks

## pdf

[PDFGenerator](https://github.com/sgr-ksmt/PDFGenerator)

## database

[YapDatabase](https://github.com/yapstudios/YapDatabase/wiki)

[Realm](https://realm.io/)

## maps

[osm](https://developers.arcgis.com/ios/OSM)

[mapbox](https://www.mapbox.com/pricing/)
50,000 map views / mo, or 50,000 mobile users / mo free

[skobbler](http://www.skobbler.com/legal#terms)
1.000.000 map usage free and .5 for 1000 next
(http://mousebird.github.io/WhirlyGlobe/tutorial/ios/digitalglobe_mapsapi.html)

[Others](https://developer.here.com/plans/api/consumer-mapping)

# create a framework

## module.modulemap

xcodeproj -> build settings -> modulemap location

```ObjC
framework module MyTargetAdapter {
  umbrella header "MyTargetAdapter.h"

  export *
  module * { export * }

  link framework "Foundation"
  link framework "UIKit"

  // Import all your public header files here.
  header "GADMAdapterMyTargetExtras.h"
  header "GADMAdapterMyTargetExtraAssets.h"
}

```

## create fat lib / framework

* info plist

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>CFBundleDevelopmentRegion</key>
	<string>$(DEVELOPMENT_LANGUAGE)</string>
	<key>CFBundleExecutable</key>
	<string>$(EXECUTABLE_NAME)</string>
	<key>CFBundleIdentifier</key>
	<string>$(PRODUCT_BUNDLE_IDENTIFIER)</string>
	<key>CFBundleInfoDictionaryVersion</key>
	<string>6.0</string>
	<key>CFBundleName</key>
	<string>$(PRODUCT_NAME)</string>
	<key>CFBundlePackageType</key>
	<string>FMWK</string>
	<key>CFBundleShortVersionString</key>
	<string>1.0</string>
	<key>CFBundleVersion</key>
	<string>$(CURRENT_PROJECT_VERSION)</string>
</dict>
</plist>
```

* build a fat framework from a sketch

```bash
#!/bin/bash
# Combine iOS Device and Simulator libraries for the various architectures
# into a single framework.

# Remove build directories if exist.
if [ -d "${BUILT_PRODUCTS_DIR}" ]; then
rm -rf "${BUILT_PRODUCTS_DIR}"
fi

# Remove framework if exists.
if [ -d "${OUTPUT_FOLDER}/${FRAMEWORK_NAME}.framework" ]; then
rm -rf "${OUTPUT_FOLDER}/${FRAMEWORK_NAME}.framework"
fi

# Create output directory.
mkdir -p "${OUTPUT_FOLDER}"

# Export framework at path.
export FRAMEWORK_LOCATION="${BUILT_PRODUCTS_DIR}/${FRAMEWORK_NAME}.framework"

# Create the path to the real framework headers.
mkdir -p "${FRAMEWORK_LOCATION}/Versions/A/Headers"

# Create the required symlinks.
/bin/ln -sfh A "${FRAMEWORK_LOCATION}/Versions/Current"
/bin/ln -sfh Versions/Current/Headers "${FRAMEWORK_LOCATION}/Headers"
/bin/ln -sfh "Versions/Current/${FRAMEWORK_NAME}" \
"${FRAMEWORK_LOCATION}/${FRAMEWORK_NAME}"

# Build static library for iOS Device.
xcodebuild -target Adapter ONLY_ACTIVE_ARCH=NO -configuration "${CONFIGURATION}" clean build -sdk "iphoneos" ARCHS="armv7 arm64" BUILD_DIR="${BUILD_DIR}" BUILD_ROOT="${BUILD_ROOT}" OBJROOT="${OBJROOT}" SYMROOT="${SYMROOT}" "${ACTION}" -UseModernBuildSystem=NO

# Build static library for iOS Simulator.
xcodebuild -target Adapter ONLY_ACTIVE_ARCH=NO -configuration "${CONFIGURATION}" clean build -sdk "iphonesimulator" ARCHS="i386 x86_64" BUILD_DIR="${BUILD_DIR}" BUILD_ROOT="${BUILD_ROOT}" OBJROOT="${OBJROOT}" SYMROOT="${SYMROOT}" "${ACTION}" -UseModernBuildSystem=NO

# Create universal framework using lipo.
lipo -create "${BUILD_DIR}/${CONFIGURATION}-iphoneos/${LIB_NAME}.a" "${BUILD_DIR}/${CONFIGURATION}-iphonesimulator/${LIB_NAME}.a" -output "${FRAMEWORK_LOCATION}/Versions/A/${FRAMEWORK_NAME}"

# Copy the public headers into the framework.
/bin/cp -a "${TARGET_BUILD_DIR}/${PUBLIC_HEADERS_FOLDER_PATH}/" \
"${FRAMEWORK_LOCATION}/Versions/A/Headers"

# Copy the framework to the library directory.
ditto "${FRAMEWORK_LOCATION}" "${OUTPUT_FOLDER}/${FRAMEWORK_NAME}.framework"

# Create Modules directory.
mkdir -p "${OUTPUT_FOLDER}/${FRAMEWORK_NAME}.framework/Modules"

# Copy the module map to modules directory.
/bin/cp -a "${MODULE_MAP_PATH}/module.modulemap" "${OUTPUT_FOLDER}/${FRAMEWORK_NAME}.framework/Modules/module.modulemap"

```

* build a fat framework from a target

```bash

#!/bin/bash
# lets print every executed statement in log
set -x
echo "Build script for custom framework with some private headers exposed"
# Fill free to use xCode warning message
# echo "error: Your error message"
# Fill free to use xCode error message
# echo "warning: Your warning message"

# Combine iOS Device and Simulator libraries for the various architectures
# into a single framework.

# Remove build directories if exist.
if [ -d "${BUILT_PRODUCTS_DIR}" ]; then
rm -rf "${BUILT_PRODUCTS_DIR}"
fi

# prepare variables

STRIPPED_OUTPUT_FOLDER="${OUTPUT_FOLDER%\"}"
STRIPPED_OUTPUT_FOLDER="${STRIPPED_OUTPUT_FOLDER#\"}"
FRAMEWORK_NAME=${FRAMEWORK_TARGET_NAME}
FRAMEWORK_FOLDER_NAME="${FRAMEWORK_NAME}.framework"
FRAMEWORK_LOCATION="${BUILD_DIR}/${CONFIGURATION}-iphoneos/${LIB_IN_FRAMEWORK_FOLDER}"
FRAMEWORK_LIB_NAME=${FRAMEWORK_NAME}
LIB_IN_FRAMEWORK_FOLDER="${FRAMEWORK_FOLDER_NAME}/${FRAMEWORK_NAME}"

# Remove framework if exists.
if [ -d "${STRIPPED_OUTPUT_FOLDER}/${FRAMEWORK_FOLDER_NAME}" ]; then
rm -rf "${STRIPPED_OUTPUT_FOLDER}/${FRAMEWORK_FOLDER_NAME}"
fi
# Create output directory.
mkdir -p ${STRIPPED_OUTPUT_FOLDER}

# Build static library for iOS Device.
xcodebuild -target "${FRAMEWORK_TARGET_NAME}" ONLY_ACTIVE_ARCH=NO -configuration "${CONFIGURATION}" clean build -sdk "iphoneos" ARCHS="armv7 arm64" BUILD_DIR="${BUILD_DIR}" BUILD_ROOT="${BUILD_ROOT}" OBJROOT="${OBJROOT}" SYMROOT="${SYMROOT}" "${ACTION}" -UseModernBuildSystem=NO

# Build static library for iOS Simulator.
xcodebuild -target "${FRAMEWORK_TARGET_NAME}" ONLY_ACTIVE_ARCH=NO -configuration "${CONFIGURATION}" clean build -sdk "iphonesimulator" ARCHS="i386 x86_64" BUILD_DIR="${BUILD_DIR}" BUILD_ROOT="${BUILD_ROOT}" OBJROOT="${OBJROOT}" SYMROOT="${SYMROOT}" "${ACTION}" -UseModernBuildSystem=NO

# Create universal framework using lipo.
lipo -create "${BUILD_DIR}/${CONFIGURATION}-iphoneos/${LIB_IN_FRAMEWORK_FOLDER}" "${BUILD_DIR}/${CONFIGURATION}-iphonesimulator/${LIB_IN_FRAMEWORK_FOLDER}" -output "${BUILD_DIR}/${CONFIGURATION}-iphoneos/${LIB_IN_FRAMEWORK_FOLDER}"

# Copy the framework to the library directory.
ditto "${FRAMEWORK_LOCATION}" "${STRIPPED_OUTPUT_FOLDER}"

```

* form a target #2

```bash
#!/bin/bash
# lets print every executed statement in log
set -x
echo "Build script for custom framework with some private headers exposed"
# Fill free to use xCode warning message
# echo "error: Your error message"
# Fill free to use xCode error message
# echo "warning: Your warning message"

# Combine iOS Device and Simulator libraries for the various architectures
# into a single framework.

# Remove build directories if exist.
if [ -d "${BUILT_PRODUCTS_DIR}" ]; then
rm -rf "${BUILT_PRODUCTS_DIR}"
fi

# prepare variables

STRIPPED_OUTPUT_FOLDER="${OUTPUT_FOLDER%\"}"
STRIPPED_OUTPUT_FOLDER="${STRIPPED_OUTPUT_FOLDER#\"}"
FRAMEWORK_NAME=${FRAMEWORK_TARGET_NAME}
FRAMEWORK_FOLDER_NAME="${FRAMEWORK_NAME}.framework"
FRAMEWORK_LOCATION="${BUILD_DIR}/${CONFIGURATION}-iphoneos/${LIB_IN_FRAMEWORK_FOLDER}"
FRAMEWORK_LIB_NAME=${FRAMEWORK_NAME}
LIB_IN_FRAMEWORK_FOLDER="${FRAMEWORK_FOLDER_NAME}/${FRAMEWORK_NAME}"

# Build static library for iOS Device.
xcodebuild -target "${FRAMEWORK_TARGET_NAME}" ONLY_ACTIVE_ARCH=NO -configuration "${CONFIGURATION}" clean build -sdk "iphoneos" ARCHS="armv7 arm64" BUILD_DIR="${BUILD_DIR}" BUILD_ROOT="${BUILD_ROOT}" OBJROOT="${OBJROOT}" SYMROOT="${SYMROOT}" "${ACTION}" -UseModernBuildSystem=NO

# Build static library for iOS Simulator.
xcodebuild -target "${FRAMEWORK_TARGET_NAME}" ONLY_ACTIVE_ARCH=NO -configuration "${CONFIGURATION}" clean build -sdk "iphonesimulator" ARCHS="i386 x86_64" BUILD_DIR="${BUILD_DIR}" BUILD_ROOT="${BUILD_ROOT}" OBJROOT="${OBJROOT}" SYMROOT="${SYMROOT}" "${ACTION}" -UseModernBuildSystem=NO

# Create universal library for the framework

# Create path variables.
IPHONEOS_FRAMEWORK_LIB="${BUILD_DIR}/${CONFIGURATION}-iphoneos/${LIB_IN_FRAMEWORK_FOLDER}"
IPHONESUMULATOR_FRAMEWORK_LIB="${BUILD_DIR}/${CONFIGURATION}-iphonesimulator/${LIB_IN_FRAMEWORK_FOLDER}"
TEMP_FAT_LIB_DIR="${BUILD_DIR}/viber-fat-iphone-simulator"
TEMP_FAT_LIB="${TEMP_FAT_LIB_DIR}/${FRAMEWORK_NAME}"

# Remove fat lib build directory if exist.
if [ -d "${TEMP_FAT_LIB_DIR}" ]; then
rm -rf "${TEMP_FAT_LIB_DIR}"
fi

# Create fat lib build directory.
mkdir -p ${TEMP_FAT_LIB_DIR}

# Create universal library for the framework using lipo.
lipo -create "${IPHONEOS_FRAMEWORK_LIB}" "${IPHONESUMULATOR_FRAMEWORK_LIB}" -output "${TEMP_FAT_LIB}"

# Replace iphoneos library with fat one
rm "${IPHONEOS_FRAMEWORK_LIB}"
cp "${TEMP_FAT_LIB}" "${IPHONEOS_FRAMEWORK_LIB}"

# Remove framework if exists.
if [ -d "${STRIPPED_OUTPUT_FOLDER}/${FRAMEWORK_FOLDER_NAME}" ]; then
rm -rf "${STRIPPED_OUTPUT_FOLDER}/${FRAMEWORK_FOLDER_NAME}"
fi

# Create output directory.
mkdir -p ${STRIPPED_OUTPUT_FOLDER}

# Copy the framework to the library directory.
ditto "${FRAMEWORK_LOCATION}" "${STRIPPED_OUTPUT_FOLDER}"
```



* build a fat lib

```bash
#!/bin/bash
# Combine iOS Device and Simulator libraries for the various architectures
# into a single fat library.


# Create output directory if it doesn't exist.
if [ ! -d "${OUTPUT_FOLDER}" ]; then
  mkdir -p "${OUTPUT_FOLDER}"
fi

# Step 1. Build static library for iOS Device.
xcodebuild -target Adapter ONLY_ACTIVE_ARCH=NO -configuration "${CONFIGURATION}" clean build -sdk "iphoneos" ARCHS="armv7 arm64" BUILD_DIR="${BUILD_DIR}" BUILD_ROOT="${BUILD_ROOT}" OBJROOT="${OBJROOT}" SYMROOT="${SYMROOT}" "${ACTION}" -UseModernBuildSystem=NO

# Step 2. Build static library for iOS Simulator.
xcodebuild -target Adapter ONLY_ACTIVE_ARCH=NO -configuration "${CONFIGURATION}" clean build -sdk "iphonesimulator" ARCHS="i386 x86_64" BUILD_DIR="${BUILD_DIR}" BUILD_ROOT="${BUILD_ROOT}" OBJROOT="${OBJROOT}" SYMROOT="${SYMROOT}" "${ACTION}" -UseModernBuildSystem=NO

# Step 3. Create universal fat library using lipo.
lipo -create "${BUILD_DIR}/${CONFIGURATION}-iphoneos/${LIB_NAME}.a" "${BUILD_DIR}/${CONFIGURATION}-iphonesimulator/${LIB_NAME}.a" -output "${OUTPUT_FOLDER}/${FAT_LIBRARY_NAME}.a"
```

## strip unnecessary architectures

```bash
strip_unnecessary_architectures() {
    FRAMEWORK_NAME=$1
    cd "${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/${FRAMEWORK_NAME}.framework/"

    file $1

    if [[ ! "${SDKROOT}" == *Simulator* ]]; then
        lipo ${FRAMEWORK_NAME} -verify_arch i386 && lipo -remove i386 ${FRAMEWORK_NAME} -output ${FRAMEWORK_NAME} && echo "i386 stripped" || echo "i386 not present"
        lipo ${FRAMEWORK_NAME} -verify_arch x86_64 && lipo -remove x86_64 ${FRAMEWORK_NAME} -output ${FRAMEWORK_NAME} && echo "x86_64 stripped" || echo "x86_64 not present"
    else
        lipo ${FRAMEWORK_NAME} -verify_arch x86_64 || { echo "Simulator architectures missing - clean and rebuild for simulator!"; exit 1; }
    fi
}

strip_unnecessary_architectures ShopChatUI
strip_unnecessary_architectures ShopChatDomain
strip_unnecessary_architectures WebRTC
strip_unnecessary_architectures ReactNative
strip_unnecessary_architectures MoPubSDKFramework

```


# testing

## Testing Right-to-Left Layouts

You can test the layout of your app for right-to-left languages without adding a right-to-left language to your project.
Follow the steps in Testing Using Pseudolanguages and choose “Right to Left Pseudolanguage” from the Application Language pop-up menu.
If you want to test the localization of a right-to-left language, choose the right-to-left language
from the Application Language pop-up menu instead. If the user interface doesn’t appear mirrored,
read Supporting Right-to-Left Languages to fix the problem.

Alternatively, to test right-to-left layouts, add launch arguments or set the equivalent user defaults.
For iOS apps, enter this line in the Arguments pane of the scheme editor:

> -AppleTextDirection YES

For Mac apps, enter both these launch arguments:

> -NSForceRightToLeftWritingDirection YES

> -AppleTextDirection YES


# architecture

[mvvm-c](https://www.youtube.com/watch?v=9VojuJpUuE8)

# how to

## Advanced Core Data

[Сергей Пронин](https://www.youtube.com/watch?v=sJsiIoj1uiI)

## quick look preview

[video](https://www.youtube.com/watch?v=q1Xf-pQMVEA)

## Debugging NSBeep Error Sound in NSResponder Method Calls

[link](https://christiantietze.de/posts/2016/11/nsresponder-finding-beep/)

## handling events in windows

[developer apple](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/WinPanel/Tasks/HandlingWindowEvents.html#//apple_ref/doc/uid/20000235-BCICIBAD)

## localisation

[MaintaingYourOwnStringsFiles](https://developer.apple.com/library/ios/documentation/MacOSX/Conceptual/BPInternational/MaintaingYourOwnStringsFiles/MaintaingYourOwnStringsFiles.html)

[script to auto merge strings](https://gist.github.com/yoichitgy/29bdd71c3556c2055cc0)


The Apple documentation implies it should be sufficient to rename an exported base language XLIFF with a language prefix to be able to import. I.e. if the base localization is English, you should be able to create a file that you can import for French localization just by renaming it from en.xliff to fr.xliff.
Renaming the file is not enough. You also need to add a target-language attribute to the fileelement.
From this:


```xml
<file original="MyApp/MyApp-Info.plist" source-language="en" datatype="plaintext">
To this:
<file original="MyApp/MyApp-Info.plist" source-language="en" datatype="plaintext" target-language="fr">
```

## xCode make // FIXME and // TODO: shows like a warnings

* add xcode build phase script - collect warnings

```bash
if [ "${CONFIGURATION}" = "Debug" ]; then
TAGS="TODO:|FIXME:"
echo "searching ${SRCROOT} for ${TAGS}"
find "${SRCROOT}" \( -name "*.swift" \) -print0 | xargs -0 egrep --with-filename --line-number --only-matching "($TAGS).*\$" | perl -p -e "s/($TAGS)/ warning: \$1/"
fi
```

# Swift code

## iOS Swift - describing type that contains oly selected types
 
```Swift
public protocol SocketData {}

extension Array : SocketData {}
extension Bool : SocketData {}
extension Dictionary : SocketData {}
extension Double : SocketData {}
extension Int : SocketData {}
extension NSArray : SocketData {}
extension Data : SocketData {}
extension NSData : SocketData {}
extension NSDictionary : SocketData {}
extension NSString : SocketData {}
extension NSNull : SocketData {}
extension String : SocketData {}

```

## ObjC Declarations

```ObjC

NS_FOUNDATION_EXPORT
NS_TYPED_ENUM
NS_EXTENSIBLE_TYPED_ENUM
NS_ASSUME_NONNULL_BEGIN
NS_ASSUME_NONNULL_END
NS_SWIFT_NAME
NS_SWIFT_NOTHROW

```

## C declarations

```ObjC
CF_RETURN_RETAINED
CF_RETURN_UNRETAINED
CF_IMPLICIT_BRIDGING_ENABLED
CF_IMPLICIT_BRIDGING_DISABLED

```

# xCode iOS Access Environment Variables in build Scheme

to access environment variables declared in build scheme from code use 

```Swift
let var = ProcessInfo.processInfo.environment["USE_SERVER"]
```

# Delete user data from NSUserDefaults

```Objective-C
NSString *appDomain = [[NSBundle mainBundle] bundleIdentifier]; 

[[NSUserDefaults standardUserDefaults] removePersistentDomainForName:appDomain];
```

# xCode #if for mac/ios switch

```Objective-C
#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_OSX
// Mac
#import <AppKit/AppKit.h>


#elif TARGET_OS_IOS
// iOS and simulator
#import <UIKit/UIKit.h>

#else
// undefined

#endif
#endif
```

# xCode environment variabes for debug


```
CG_CONTEXT_SOW_BACKTRACE=1
CGBITMAP_CONTEXT_LOG_ERRORS=1
IIO_DEBUG_METADATA=1
```
 
# ImageIO's way to write a TIFF image with LZW compression

(https://lists.apple.com/archives/quartz-dev/2010/Sep/msg00003.html)

Does anyone know if there's a way to write a TIFF image with LZW compression (or some other lossless compression) using the Image I/O framework on the Mac?

(CGImageSource/CGImageDestination)

I know that NSBitmapImageRep supports LZW, but Image I/O makes it easy to keep the original metadata intact, which is a requirement in my application.

CGImageDestinationAddImage takes an options dictionary. You could try specifying kCGImageDestinationLossyCompressionQuality with a value of 1.0. There's also a key kCGImagePropertyTIFFCompression, but I don't see any documentation for what the possible values are.


The values are integers that identify specific algorithms, as defined in the TIFF spec.

They're the same as in NSBitmapImageRep.h:
```
NSTIFFCompressionNone  = 1,
    NSTIFFCompressionCCITTFAX3  = 3,  /* 1 bps only */
    NSTIFFCompressionCCITTFAX4  = 4,  /* 1 bps only */
    NSTIFFCompressionLZW  = 5,
    NSTIFFCompressionJPEG  = 6,  /* No longer supported for input or output */
    NSTIFFCompressionNEXT  = 32766,	/* Input only */
    NSTIFFCompressionPackBits  = 32773,
    NSTIFFCompressionOldJPEG  = 32865	
```

You want 5, LZW.

# test credit cards

[link](https://www.paypalobjects.com/en_US/vhelp/paypalmanager_help/credit_card_numbers.htm)

American Express
378282246310005

American Express
371449635398431

American Express Corporate
378734493671000

Australian BankCard
5610591081018250

Diners Club
30569309025904

Diners Club
38520000023237

Discover
6011111111111117

Discover
6011000990139424

JCB
3530111333300000

JCB
3566002020360505

MasterCard
5555555555554444

MasterCard
5105105105105100

Visa
4111111111111111

Visa
4012888888881881

Visa
4222222222222

Note : Even though this number has a different character count than the other test numbers, it is the correct and functional number.

Processor-specific Cards

Dankort (PBS)
76009244561

Dankort (PBS)
5019717010103742

Switch/Solo (Paymentech)
6331101999990016

# Apple sandbox

[guide, review](https://developer.apple.com/library/content/documentation/Security/Conceptual/AppSandboxDesignGuide/AppSandboxInDepth/AppSandboxInDepth.html#//apple_ref/doc/uid/TP40011183-CH3-SW8)


# Sample Library Style Core Data Apps with iCloud Integration

[sample](https://ossh.com.au/design-and-technology/software-development/sample-library-style-ios-core-data-app-with-icloud-integration/)

# xCode Denied launch request

Solution 2: open Keychain Access -> choose System, All Items -> delete certificate Apple Worldwide Developer Relations Certification Authority
[link]https://stackoverflow.com/questions/52415694/ipad-has-denied-the-launch-request-after-update-to-ios-12/52584195#52584195

