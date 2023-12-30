# RIG-Linux - (Random Image Generator)
WIP project, currently at beta stage.

## This program creates images from random pixels, based on user input.
Users can currently specify:
- Size (width x height)
- To use the alpha channel or not in PNG (transparency)
- Image count (how many images will be generated)



## Todo:
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

## Supported OS-es
GNU/Linux (and maybe MacOS and BSD systems).
If it has the dependencies and mets the POSIX standard, it should probably run, but the program only has official support for Linux.



## Dependencies
You need to have `clang` `make` `git` installed on your GNU/Linux machine.


## How to download and build
0. You need to have the dependencies _(listed in their section above)_ installed. If you don't know how to do it, search how to install _*package name*_ on _*your Linux distro's name*_
1. $ `git clone https://github.com/SzBenedek2006/RIG-Linux.git`
2. $ `cd RIG-Linux/`
3. Just run $ `make`. It will make an executable named RIG-_your\_architecture_.
4. Now you can try the program out by running $ `./RIG-_your_architecture_ -h`

