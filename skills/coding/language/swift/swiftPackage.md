## Swift Package Manager

### Package file structure

- Package Folder/ (PackageName)

- - Package.swift

- - Readme.md

- - Sources/

- - - TargetFolder/ (TargetName)

- - - - TargetFiles ...

- - Tests/

- - - TestsTargetFolder/ (TestsTargetName)

- - - - TargetFiles

### Package.swift - manifest file example 

```
// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

/*
 The 'version: x.x.x' comment used by CI for incmenting developer builds.
 Do not remove it.
 For marking released bunles tags git-tags should be used.
 */

/*
 version: 1.0.1
 */

let package = Package(
    name: "TruUCore",
    defaultLocalization: "en",
    platforms: [
        .iOS(.v13)
    ],
    products: [
        // Products define the executables and libraries a package produces, and make them visible to other packages.
        .library(
            name: "TruUCore",
            targets: ["TruUCore"])
    ],
    dependencies: [
        // Dependencies declare other packages that this package depends on.
        .package(path: "../TruUTelemetry"),
        .package(name: "SwiftStomp", url: "git@bitbucket.org:truudev/stomp-client-for-apple.git", from: "0.0.0"),
        .package(url: "https://github.com/SomeRandomiOSDev/CBORCoding.git", from: "1.0.0"),
        .package(name: "CryptorECC", url: "https://github.com/IBM-Swift/BlueECC.git", from: "1.2.5"),
        .package(url: "https://github.com/swift-package-manager/SwiftyRSA.git", from: "1.6.0"),
        .package(name: "SwiftProtobuf", url: "https://github.com/apple/swift-protobuf.git", from: "1.6.0")
    ],
    targets: [
        // Targets are the basic building blocks of a package. A target can define a module or a test suite.
        // Targets can depend on other targets in this package, and on products in packages this package depends on.
        .target(
            name: "TruUCore",
            dependencies: ["TruUTelemetry", "SwiftStomp", "CBORCoding", "CryptorECC", "SwiftyRSA", "SwiftProtobuf"],
            resources: [.copy("Transmit/Protobuf/TruUTransmitData.proto")]),
        .testTarget(
            name: "TruUCoreTests",
            dependencies: ["TruUCore"])
    ]
)
```
