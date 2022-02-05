

# android studio


## Install Android Studio on Fedora 26 - CIALU.NET

[source](https://cialu.net/install-android-studio-fedora-26/) 
Fedora 26 is pretty rock stable and fast. Let's go to install Android Studio IDE and find how it works on this operative system.
Apr 20th, 2017 at 11:59 AM

## better one

[source](https://www.hiroom2.com/2017/09/14/fedora-26-android-studio-2-3-en/)
Fedora 26: Install Android Studio 2.3
This article will describe installing Android Studio 2.3.

```cmd
cat <<EOF | sudo tee /usr/local/share/applications/android-studio.desktop [Desktop Entry] Type=Application Name=Android Studio Icon=/opt/android-studio/bin/studio.png Exec=env _JAVA_OPTIONS=-Djava.io.tmpdir=/var/tmp /opt/android-studio/bin/studio.sh Terminal=false Categories=Development;IDE; EOF
```