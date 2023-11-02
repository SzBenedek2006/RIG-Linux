#include "PNG_generator.c"
#include "dir_creator.c"
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {

    printf("Welcome to RIG\n\n");


    // TODO: Implement arguments stuff

    // Check max arg count

/*
int width = 10;  // width of the image
int height = 10; // height of the image


*/



    // Do logic for arg1, 2 3, etc...



    srand((unsigned int)time(NULL)); // Seed the random number generator
    int i;
    int errorCount = 0;
    for (i = 0 + 1; i < 1000 + 1; i++) {
        char imagename[30];


        dirCreatorLinux("out");

        sprintf(imagename, "out/random_image%d.pgm", i);
        errorCount = errorCount + generateImage(imagename);
    }


    if (errorCount == 0) {
        printf("%d random image(s) generated successfully.\n", i - 1);
    } else {
        printf("Random image(s) generated with %d error(s).\n", errorCount);
    }


    return 0;
}
