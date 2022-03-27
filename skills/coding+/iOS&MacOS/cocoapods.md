<https://stackoverflow.com/questions/30244675/how-can-i-modify-other-ldflags-via-cocoapods-post-install-hook>

```
post_install do |installer|
  installer.pods_project.build_configuration_list.build_configurations.each do |configuration|
    configuration.build_settings['CLANG_WARN_QUOTED_INCLUDE_IN_FRAMEWORK_HEADER'] = 'YES'

    if configuration.name == 'Develop'
      configuration.build_settings['SWIFT_ACTIVE_COMPILATION_CONDITIONS'] = ['DEVELOP']
      configuration.build_settings['SWIFT_COMPILATION_MODE'] = 'singlefile'
      configuration.build_settings['SWIFT_OPTIMIZATION_LEVEL'] = '-Onone'
      configuration.build_settings['GCC_OPTIMIZATION_LEVEL'] = '0'
      elsif configuration.name == 'Develop-Coherent'
      configuration.build_settings['SWIFT_ACTIVE_COMPILATION_CONDITIONS'] = ['DEVELOP']
      configuration.build_settings['SWIFT_COMPILATION_MODE'] = 'singlefile'
      configuration.build_settings['SWIFT_OPTIMIZATION_LEVEL'] = '-Onone'
      configuration.build_settings['GCC_OPTIMIZATION_LEVEL'] = '0'
      elsif configuration.name == 'Develop-Cloud-Coherent'
      configuration.build_settings['SWIFT_ACTIVE_COMPILATION_CONDITIONS'] = ['DEVELOP']
      configuration.build_settings['SWIFT_COMPILATION_MODE'] = 'singlefile'
      configuration.build_settings['SWIFT_OPTIMIZATION_LEVEL'] = '-Onone'
      configuration.build_settings['GCC_OPTIMIZATION_LEVEL'] = '0'
    end
  end
    
  installer.pods_project.targets.each do |target|
    target.build_configurations.each do |config|
      config.build_settings['IPHONEOS_DEPLOYMENT_TARGET'] = '13.0'

      if config.name == 'Develop'
        config.build_settings['SWIFT_ACTIVE_COMPILATION_CONDITIONS'] = ['DEVELOP']
        elsif config.name == 'Develop-Coherent'
        config.build_settings['SWIFT_ACTIVE_COMPILATION_CONDITIONS'] = ['DEVELOP']
        elsif config.name == 'Develop-Cloud-Coherent'
        config.build_settings['SWIFT_ACTIVE_COMPILATION_CONDITIONS'] = ['DEVELOP']
        elsif config.name == 'Staging-Coherent'
        config.build_settings['SWIFT_ACTIVE_COMPILATION_CONDITIONS'] = ['STAGING_COHERENT']
        elsif config.name == 'Staging-Cloud-Coherent'
        config.build_settings['SWIFT_ACTIVE_COMPILATION_CONDITIONS'] = ['STAGING_COHERENT']
      end
    end
  end

  # when using pod 'Firebase/Analytics' with '7.4-M1' suffix
  # we require to manually put the -ObjC flag in OTHER_LDFLAGS of xcconfig
  installer.aggregate_targets.each do |aggregate_target|
    puts "Appending -ObjC to xcconfigs of target: #{aggregate_target.name}\r\n"
    aggregate_target.xcconfigs.each do |config_name, config|
      config.other_linker_flags[:simple] << '-ObjC'
      xcconfig_path = aggregate_target.xcconfig_path(config_name)
      config.save_as(xcconfig_path)
    end
  end
end
```
