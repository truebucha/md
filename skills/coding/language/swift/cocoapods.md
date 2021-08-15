
# update without repo update
pod update --no-repo-update

# This is the solution when you are receiving the "Operation not permitted" error.


```cmd
$ mkdir -p $HOME/Software/ruby
$ export GEM_HOME=$HOME/Software/ruby
$ gem install cocoapods
[...]
1 gem installed
$ export PATH=$PATH:$HOME/Software/ruby/bin
$ pod --version
```

Create .bash_profile file with contents

```txt
export PATH=$PATH:$HOME/Software/ruby/bin
export GEM_HOME=$HOME/Software/ruby
```
# to lint libraries wrote in swift 3.0

place "swift-version" file besides podspec file (root of the pod folder)

echo "3.0" >> .swift-version

# xCode build time speedup optimization

[shaving 50% off](https://labs.spotify.com/2013/11/04/shaving-off-time-from-the-ios-edit-build-test-cycle/)

[speed up build](https://habrahabr.ru/post/317650/)

```Ruby
Pod file example

 install! 'cocoapods',
 :deterministic_uuids => false


workspace 'QromaScan.xcworkspace'

development_pods = true
# list of 3.3 swif targets .
swift3Targets = []
swift3InheritanceTargets = ['NohanaImagePicker']

post_install do |installer|
    
    installer.pods_project.targets.each do |target|
        
        if swift3InheritanceTargets.include? (target.name)
            
            target.build_configurations.each do |config|
                config.build_settings['SWIFT_SWIFT3_OBJC_INFERENCE'] = 'On'
            end
        end
        
        if swift3Targets.include? (target.name)
            
            target.build_configurations.each do |config|
                config.build_settings['SWIFT_VERSION'] = '3.3'
            end
        else
        
            target.build_configurations.each do |config|
                config.build_settings['SWIFT_VERSION'] = '4.1'
            end
        end
        
    end
    
    # installer.pods_project.targets.each do |target|
    #   target.build_configurations.each do |configuration|
    #        target.build_settings(configuration.name)['ACTIVE_ARCH_ONLY'] = 'NO'
    #    end
    # end

    
    puts("Update debug pod settings to speed up build time")
    Dir.glob(File.join("Pods", "**", "Pods*{debug,Private}.xcconfig")).each do |file|
        File.open(file, 'a') { |f| f.puts "\nDEBUG_INFORMATION_FORMAT = dwarf" }
    end

    next if development_pods

    puts("Update copy pod resources only once to speed up build time")

    Dir.glob(installer.sandbox.target_support_files_root + "Pods-*/*.sh").each do |script|
        flag_name = File.basename(script, ".sh") + "-Installation-Flag"
        folder = "${TARGET_BUILD_DIR}/${UNLOCALIZED_RESOURCES_FOLDER_PATH}"
        file = File.join(folder, flag_name)
        content = File.read(script)
        content.gsub!(/set -e/, "set -e\nKG_FILE=\"#{file}\"\nif [ -f \"$KG_FILE\" ]; then exit 0; fi\nmkdir -p \"#{folder}\"\ntouch \"$KG_FILE\"")
        File.write(script, content)
    end

    puts("Please clean project after pod install/update = CMD+SHIFT+K in xCode")
end
```