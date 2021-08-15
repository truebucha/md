### [swift-protobuf](https://github.com/apple/swift-protobuf)

### brew install

```
brew install swift-protobuf
```

### generate from proto file 

```
protoc --swift_out=. --swift_opt=Visibility=Public dAir.proto
```

[options](https://github.com/apple/swift-protobuf/blob/master/Documentation/PLUGIN.md#generation-option-visibility---visibility-of-generated-types)
