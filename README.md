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


## Dependencies
`clang` `make` `git` and a linux machine



## Build:
0. You need gcc compiler.
1. Just run $ `make`. It will make an executable named RIG-_your_architecture_.

