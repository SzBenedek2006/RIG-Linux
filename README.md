# RIG-Linux - (Random Image Generator)
WIP project, currently at beta stage.

## This program creates images from random pixels, based on user input.
Users can currently specify:
- Size (width x height)
- The use of alpha channel in PNG (transparency)
- Image count (how many images will be generated)
- To put the images in android internal storage instead of termux home directory when specified
- Output debug info



## Dependencies
You need to have `clang` `make` `git` installed on your GNU/Linux machine.
Also you have to have `libpng` installed. On Fedora you also need `libpng-devel`.

**Fedora**
```Fedora
sudo dnf install libpng-devel clang make git
```

**Termux**
```Termux
pkg install libpng clang make git
```

**Arch**
```Arch
sudo pacman -Syu libpng clang make git
```


## How to download and build
0. You need to have the dependencies _(listed in their section above)_ installed. If you don't know how to do it, search how to install _*package name*_ on _*your Linux distro's name*_
1. $ `git clone https://github.com/SzBenedek2006/RIG-Linux.git`
2. $ `cd RIG-Linux/`
3. Just run $ `make`. It will make an executable named RIG-<your\_architecture>.
4. Now you can try the program out by running $ `./RIG-<your_architecture> -h`


## Todo / The current state of the project
- [ ] More output format
- [x] Basic user input handling
- [ ] User input handling for
  - [ ] Formats
    - [x] PNG
    - [ ] JPG
      - [ ] Compression toggle
    - [ ] Webp
    - [ ] HEIC
  - [ ] Choosing between b&w and color output
  - [x] Resolution
  - [x] Image count
  - [x] Alpha channel (PNG)
- [x] Fix memory leak
- [x] Make use of termux setup-external-storage
- [x] Add debug option
  - [ ] Add more debug messages and make use of the stderr output.
  - [ ] Make printing debug messages a function and fix rendering issue with the progressbar
- [ ] Add haptic feedback on Android and speaker feedback in other supported devices
- [x] Add a progressbar
- [ ] Add CLI completion

## Supported OS-es
GNU/Linux, Android/Linux (see the Termux section), and maybe MacOS and BSD systems.
If it has the dependencies and mets the POSIX standard, it should probably run, but the program only has official support for Linux and Android (Termux).

## Termux
The program can be run in termux after installing the dependencies.
Since the Termux update, you can use  `--termux-external` command to put the output files to your internal storage.



