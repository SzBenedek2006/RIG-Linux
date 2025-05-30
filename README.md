# RIG-Linux - (Random Image Generator)
[![GitHub stars](https://img.shields.io/github/stars/SzBenedek2006/RIG-Linux.svg)](https://github.com/SzBenedek2006/RIG-Linux/stargazers)
 [![License](https://img.shields.io/github/license/SzBenedek2006/RIG-Linux.svg)](https://github.com/SzBenedek2006/RIG-Linux/blob/main/GPL-3.0) [![Code Size](https://img.shields.io/github/languages/code-size/SzBenedek2006/RIG-Linux.svg)](https://github.com/SzBenedek2006/RIG-Linux)


## This program creates images from random pixels, based on user input.
Users can currently specify:

- **-s** or **--size** \<width height\>
	- Changed the order in 2.0!
- **-c** or **--count** \<number\>
	- This many images will be generated.
- **-f** or **--format** \<image format\>
	- It supports png or jpg (jpeg) formats. When not used, defaults to png.
- **-a** or **--alpha**
    - Use transparent pixels in png. With jpeg, this will be ignored.
- **--termux-external**
	- When used in Termux, images will be moved to your internal storage.
- **-d** or **--debug**
	- Print debug info.
- **--rgb** or **--RGB** \<RED GREEN BLUE\>
	- This sets the values in each channel, so you can make colorful or darker images.
- **--sensor-noise**
	- Puts lines on the pictures, like image sensors with high iso.
- **-q** or **--quality**
  - Specifies the quality for JPEG images, unaffective in png.
- **-h** or **--help**
	- Prints this message to console.

## Download
Head to the [releases](https://github.com/SzBenedek2006/RIG-Linux/releases) section and download from there if I don't forget to release the executable files. After unpacking, if you have permission issues, usually a `chmod +x` solves the issue. If you don't find the executables you need, [build from source](https://github.com/SzBenedek2006/RIG-Linux?tab=readme-ov-file#how-to-download-and-build-from-source).


## Dependencies
You need to have `clang`, `make`, `git`, `libpng` and a variant of `libjpeg` installed on your GNU/Linux machine.

**Fedora**
```Fedora
sudo dnf update && sudo dnf install libpng-devel libjpeg-turbo-devel gcc make git
```

**Termux**
```Termux
apt update && apt install libpng libjpeg-turbo clang make git
```

**Arch**
```Arch
sudo pacman -Syu libpng libjpeg-turbo gcc make git
```

**Debian**
```Debian
sudo apt update && sudo apt install gcc make git libpng-dev libjpeg-dev
```


## How to download and build from source
0. You need to have the dependencies _(listed in their section above)_ installed. If you don't know how to do it, search how to install _*package name*_ on _*your Linux distro's name*_
1. $ `git clone --recurse-submodules https://github.com/SzBenedek2006/RIG-Linux.git`
2. $ `cd RIG-Linux/`
3. $ `make` It will make an executable named RIG-\<your\_architecture\>. (For example RIG-x86_64 or RIG-aarch64)
4. $ `bin/RIG-\<your_architecture\> -h` This will run the program and print the help message. If you don't know your architecture, try autocomplete after `./RIG-` with the tab key.

### Updating
1. $ `git pull`

**IMPORTAN: If you cloned the repo before the addition of the stb library directory (or before an stb update), you should run the following command too, after the first.**
2. $ `git submodule update --init --recursive`


## Todo / The current state of the project
- [x] More output format
- [x] Basic user input handling
- [ ] User input handling for
  - [x] Formats
    - [x] PNG
    - [x] JPG
      - [x] Compression toggle
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
- [ ] Move to stb libraries for image handling.
- [x] Add an automatic release workflow
  - [ ] Support more architectures
  - [ ] Support automatically making a new tag based on the version in version.h

## Supported OS-es
GNU/Linux, Android/Linux (see the Termux section), and maybe MacOS and BSD systems.
If it has the dependencies and meets the POSIX standard, it should probably run, but the program only has official support for Linux and Android (Termux).

## Termux
The program can be run in Termux after installing the dependencies.
Since the Termux update, you can use  `--termux-external` command to put the output files to your internal storage.
This is recommended for easier access to the generated pictures.
