#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jpeglib.h"



/* Function to write a JPEG file */
void write_JPEG_file(char *filename, long width, long height, int quality) {
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *outfile;
    JSAMPROW row_pointer[1];
    JSAMPLE *image_buffer;

    // Allocate memory for the image buffer
    image_buffer = (JSAMPLE *)malloc(width * height * 3 * sizeof(JSAMPLE));
    if (image_buffer == NULL) {
        fprintf(stderr, "Failed to allocate memory for image buffer\n");
        exit(1);
    }

    // Generate random image
    //generate_random_image(width, height, image_buffer);


    // srand(time(NULL)); // Seed for random number generation (already did in the main function)

    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            int index = (i * width + j) * 3; // Calculate index for RGB values
            image_buffer[index] = rand() % 256; // Red
            image_buffer[index + 1] = rand() % 256; // Green
            image_buffer[index + 2] = rand() % 256; // Blue
        }
    }

    // Initialize JPEG compression object
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    // Open output file
    if ((outfile = fopen(filename, "wb")) == NULL) {
        fprintf(stderr, "can't open %s\n", filename);
        exit(1);
    }
    jpeg_stdio_dest(&cinfo, outfile);

    // Set parameters for compression
    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE);

    // Start compression
    jpeg_start_compress(&cinfo, TRUE);

    // Write scan lines
    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = &image_buffer[cinfo.next_scanline * width * 3];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    // Finish compression
    jpeg_finish_compress(&cinfo);

    // Release resources
    fclose(outfile);
    jpeg_destroy_compress(&cinfo);
    free(image_buffer);
}
