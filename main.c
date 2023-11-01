#include "pgm_generator.c"
#include "dir_creator.c"
#include <stdio.h>

int main() {

    printf("Welcome to RIG\n\n");



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
