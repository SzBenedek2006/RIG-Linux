#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define WIDTH 10 //46340
#define HEIGHT 10 //46340
#define MAX_GRAY_VALUE 255


int generateImage(const char *filename) {                                  // generate function
    FILE *imageFile = fopen(filename, "wb");                                // Opening imageFile to read write binary

    // Check if file opened successfully
    if (!imageFile) {
        printf("Error creating the image file. (pgm_generator)\n");
        return 1;
    }

    // Write the PGM header
    fprintf(imageFile, "P5\n%d %d\n%d\n", WIDTH, HEIGHT, MAX_GRAY_VALUE);

    unsigned char pixel;


    // Generate and write random pixel values
    for (unsigned long long int i = 0; i < WIDTH * HEIGHT; ++i) {
        pixel = rand() % (MAX_GRAY_VALUE + 1);
        fwrite(&pixel, sizeof(unsigned char), 1, imageFile);
    }

    fclose(imageFile);
    return 0;
}





// TODO: Implement libpng conversion













