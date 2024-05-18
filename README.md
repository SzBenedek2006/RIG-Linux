# RIG-Linux - (Random Image Generator)
This project is work in progress... [![GitHub stars](https://img.shields.io/github/stars/SzBenedek2006/RIG-Linux.svg)](https://github.com/SzBenedek2006/RIG-Linux/stargazers)
 [![License](https://img.shields.io/github/license/SzBenedek2006/RIG-Linux.svg)](https://github.com/SzBenedek2006/RIG-Linux/blob/main/GPL-3.0) [![Code Size](https://img.shields.io/github/languages/code-size/SzBenedek2006/RIG-Linux.svg)](https://github.com/SzBenedek2006/RIG-Linux)



## This program creates images from random pixels, based on user input.
Users can currently specify:
- Size (width x height)
- The use of alpha channel in PNG (transparency)
- Image count (how many images will be generated)
- To put the images in android internal storage instead of termux home directory when specified
- Output debug info



## Dependencies
You need to have `clang`, `make`, `git`, and `libpng` installed on your GNU/Linux machine.
On Fedora you also need `libpng-devel`.

**Fedora**
```Fedora
sudo dnf install libpng-devel gcc make git
```

**Termux**
```Termux
pkg install libpng libjpeg-turbo clang make git
```

**Arch**
```Arch
sudo pacman -Syu libpng gcc make git
```

**Debian**
```Debian
pkg install libpng-dev gcc make git
```


## How to download and build from source
0. You need to have the dependencies _(listed in their section above)_ installed. If you don't know how to do it, search how to install _*package name*_ on _*your Linux distro's name*_
1. $ `git clone https://github.com/SzBenedek2006/RIG-Linux.git`
2. $ `cd RIG-Linux/`
3. $ `make` It will make an executable named RIG-<your\_architecture>. (For example RIG-x86_64 or RIG-aarch64)
4. $ `./RIG-<your_architecture> -h` This will run the program and print the help message. If you don't know your architecture, try autocomplete after `./RIG-` with the tab key.


## Todo / The current state of the project
- [x] More output format
- [x] Basic user input handling
- [ ] User input handling for
  - [x] Formats
    - [x] PNG
    - [x] JPG
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
  - [x] Make printing debug messages a function and fix rendering issue with the progressbar
- [ ] Add haptic feedback on Android and speaker feedback in other supported devices
- [x] Add a progressbar
- [ ] Add CLI completion
- [ ] Add a calculator for file size

## Supported OS-es
GNU/Linux, Android/Linux (see the Termux section), and maybe MacOS and BSD systems.
If it has the dependencies and mets the POSIX standard, it should probably run, but the program only has official support for Linux and Android (Termux).

## Termux
The program can be run in Termux after installing the dependencies.
Since the Termux update, you can use  `--termux-external` command to put the output files to your internal storage.




