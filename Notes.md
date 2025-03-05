# SDL2 Sources

* [SDL](https://www.libsdl.org/download-2.0.php)
* [SDL_image](https://www.libsdl.org/projects/SDL_image/)
* [SDL_mixer](https://www.libsdl.org/projects/SDL_mixer/)
* [SDL_net](https://www.libsdl.org/projects/SDL_net/)
* [SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/)
* [SDL projects](https://www.libsdl.org/projects/)

# SDL2 changelog

* [Changelog](https://www.libsdl.org/tmp/SDL/WhatsNew.txt)

# get paths in SDL2 (Resources/Preferences)

* https://wiki.libsdl.org/SDL_GetBasePath - Use this function to get the directory where the application was run from. This is where the application data directory is.
* https://wiki.libsdl.org/SDL_GetPrefPath - Use this function to get the "pref dir". This is meant to be where the application can write personal files (Preferences and save games, etc.) that are specific to the application. This directory is unique per user and per application.

# Bundling Mac OS X application

### change linked frameworks

http://stackoverflow.com/questions/1482682/how-to-distribute-a-mac-os-x-with-dependent-libraries
http://stackoverflow.com/questions/1596945/building-osx-app-bundle

List linked frameworks:
```bash
otool -L executable_name
```

Change linked frameworks:
```bash
install_name_tool -change existing_path_to_dylib @executable_path/blah.dylib executable_name
```

### codesign app for gatekeeper (if app is downloaded as zip from internet)

http://stackoverflow.com/questions/13204407/how-to-codesign-an-existing-mac-os-x-app-file-for-gatekeeper

```bash
ort CODESIGN_ALLOCATE="/Applications/Xcode.app/Contents/Developer/usr/bin/codesign_allocate"
codesign --force --sign "Developer ID Application: <my name>" /path/to/my.app
```

### netbeans code assistance problem

http://thegreyblog.blogspot.de/2014/02/how-to-include-apple-frameworks-headers.html
https://github.com/emcrisostomo/link-osx-framework-headers
http://stackoverflow.com/questions/8067329/how-to-include-apple-frameworks-on-eclipse-cdt



# "bundling/installing" Ubuntu Linux application

### install libs
```bash
sudo apt install libsdl2-*
sudo apt install libbox2d*
```

### install needed packages under Ubuntu 19.10

It was a little mess to figure out the right versions. Maybe next time staying on a Ubuntu LTS version would be better for installing the needed stuff.

```bash
$ sudo apt-get install libibus-1.0-dev=1.5.21-1~exp2ubuntu2 libsdl2-dev=2.0.10+dfsg1-1ubuntu1 libpulse-dev=1:13.0-1ubuntu1.1 libglib2.0-dev=2.62.1-1 libpcre3-dev=2:8.39-12 libpcre3=2:8.39-12 libselinux1-dev=2.9-2 libpcre2-dev=10.32-5 libpcre16-3=2:8.39-12 libpcre2-8-0=10.32-5 libpcre2-16-0=10.32-5
```


### application icon

https://wiki.ubuntuusers.de/.desktop-Dateien/

* /usr/share/applications/APP_NAME.desktop
* /usr/share/icons/

### application menu entry

https://wiki.ubuntuusers.de/.directory-Dateien/
https://developer.gnome.org/integration-guide/stable/desktop-files.html.de

### application resources

* /usr/share/APP_NAME/resources (????)


# Windows gcc developng environment

* [gcc with CygWin/MinGW](https://www.libsdl.org/extras/win32/gcc.html)

# "bundling" ios apps

### console lipo => show lib archs

```bash
lipo -info libSDL2.a
```

### console lipo => build fat lib with all archs example see also next point

```bash
lipo templibs/*.a -create -output lib/libSDL2.a
```

### sdl_ios shell script to build fat libs with all archs of sdl

```bash
#!/bin/bash

rm -rf templibs
mkdir templibs

rm -rf build

xcodebuild -configuration Release -target libSDL -arch i386 -sdk iphonesimulator clean build
cp build/Release-iphonesimulator/libSDL2.a templibs/libSDL2_i386.a
xcodebuild -configuration Release -target libSDL -arch x86_64 -sdk iphonesimulator clean build
cp build/Release-iphonesimulator/libSDL2.a templibs/libSDL2_x86_64.a
xcodebuild -configuration Release -target libSDL -arch armv7 -sdk iphoneos clean build
cp build/Release-iphoneos/libSDL2.a templibs/libSDL2_armv7.a
xcodebuild -configuration Release -target libSDL -arch armv7s -sdk iphoneos clean build
cp build/Release-iphoneos/libSDL2.a templibs/libSDL2_armv7s.a
xcodebuild -configuration Release -target libSDL -arch arm64 -sdk iphoneos clean build
cp build/Release-iphoneos/libSDL2.a templibs/libSDL2_arm64.a

rm -rf lib
mkdir lib

lipo templibs/*.a -create -output lib/libSDL2.a

rm -rf templibs
rm -rf build
```

https://github.com/ThirdPartyNinjas/sdl_ios

### default icon sizes

https://gist.github.com/uebo/a6cfecd08900c889af11

https://developer.apple.com/library/ios/qa/qa1686/_index.html

### icon/splash screen generator

http://zeppelindev.com/splash.html#none
http://zeppelindev.com/splash.html#icon

### control simulator over commandline

http://stackoverflow.com/questions/26031601/xcode-6-launch-simulator-from-command-line

List known simulators:
```bash
xcrun instruments -s
```

Start Simulator:
```bash
xcrun instruments -w "iPhone 4s (9.2) [2F90DA02-22C4-4175-8BAF-C413458635E8]"
```

Upload App to simulator:
```bash
xcrun simctl install booted ./MyApp.app/
```

Start installed app in simulator:
```bash
xcrun simctl launch booted "com.yourcompany.MyApp"
```

### ios check if app is code signed

```bash
codesign --verify ./MyApp.app
```

### ios show available codesign identities

```bash
security find-identity -v -p codesigning
```

### ios code sign app (hack?)

A modified PackageApplication pearl script is needed. This is located at.

```bash
/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/usr/bin/PackageApplication
```

Read for details: http://cutting.io/posts/packaging-ios-apps-from-the-command-line/

```bash
// use hash if signing identity, output path has to be absolute.
xcrun -sdk iphoneos PackageApplication -v "MyApp.app" -output /Users/csg/Dropbox/c/sdl/sdl-project-template/build/ios.simulator/MyApp.ipa --sign "48BA85AF4E07F09EECC630109475265BA9D985EA"

// following signing identity not working
xcrun -sdk iphoneos PackageApplication -v "MyApp.app" -o "MyApp.ipa" --sign "\"iPhone Developer: Christian Sonntag (7UA9WA98EV)\""
```

### ios simulator logs

```bash
~/Library/Logs/DiagnosticReports/
```

http://www.wonderousponder.com/how-to-find-crash-log-of-ios-simulator/

### ios hacking and links

!!! https://gist.github.com/hramos/774017
!!! http://mokagio.github.io/tech-journal/2015/03/12/xcode-list-available-devices.html
http://hub.jmonkeyengine.org/t/non-apple-mac-ios-iphone-toolchain-various-information/25630
http://www.pmbaty.com/iosbuildenv/
https://code.google.com/archive/p/ios-toolchain-based-on-clang-for-linux/wikis/HowTo_en.
http://dduan.net/post/2015/02/build-and-run-ios-apps-in-commmand-line/
http://mgrebenets.github.io/xcode/2015/02/18/whats-your-destination/
https://www.diawi.com/

### ios continuous integration

!!! https://fastlane.tools/


# Xcode links

* [Building from the Command Line with Xcode FAQ](https://developer.apple.com/library/ios/technotes/tn2339/_index.html)


# gcc stuff

### GCC dump preprocessor defines

```bash
g++ -DFOOBAR -dM -E - < /dev/null
```
