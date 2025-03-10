# SDL project template

This project is a starting point to build an SDL Mac app, iOS App or Linux executeable at the moment. It can be used without Xcode and you can use your favourite ide. Netbeans is working very well for me (build&run, Code Assistance,...). The Netbeans project settings are included in this repository. I think Eclipse maybe can be used as well.

It uses a normal Makefile and generates an OS X App bundle with all needed files (Libraries, Resources). Change the Makefiles to your own needs.

### General make usage

Builds a executable app for host os (Linux/macOS at the moment). 

```make``` - compile and build app bundle

```make run``` - starts the app

```make clean``` - delete executable and all compiled .o files

### make a specific target

```TARGET=iOS_Simulator make``` - compile and build app bundle

```TARGET=iOS_Simulator make run``` - starts the app

```TARGET=iOS_Simulator make clean``` - delete executable and all compiled .o files

Targets: **Linux**, **Darwin**, MinGW32, MinGW64, **iOS_Device**, **iOS_Simulator**

> Only bold targets are used and are "working" at the moment!

### Included OS X Frameworks/Libraries

* Box2D.framework
* SDL2.framework
* SDL2_image.framework
* SDL2_mixer.framework
* SDL2_net.framework

### Workarounds

#### Library linking workaround

Due to manual app bundling the compiler links to a wrong (@rpath) relative library location and not to the libraries in the "Frameworks" app bundle folder (@executable_path). This fact needs a little workaround with otool and install_name_tool. See also [Notes.md](Notes.md).

#### Header files code assistance symlink workaround for Netbeans / Eclipse

Most IDEs don't recognize the OS X Library structure (with subfolders) and can't index the header files correctly. For this reason there are symlinks to the Library header files in the folder "ide_includes". See also [Notes.md](Notes.md).

### Todo

* add code signing for gate keeper?
* support linux/windows as well?
* maybe the use of cmake instead of make would be better ;-)

### Bugs

* no known bugs yet :D