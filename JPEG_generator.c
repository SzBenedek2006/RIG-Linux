#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <time.h>
#include <stdint.h>
#include "jpeglib.h"
#include "JPEG_generator.h"
#include "my_utils.h"


/* Function to write a JPEG file */
void generateJPEG(char *filename, long width, long height, int quality, uint8_t r, uint8_t g, uint8_t b, bool random_multiplier) {
    float multiplier = 0.0f;
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *outfile;
    JSAMPROW row_pointer[1];
    JSAMPLE *image_buffer;

    // Allocate memory for the image buffer
    image_buffer = (JSAMPLE *)malloc(width * height * 3 * sizeof(JSAMPLE));
    if (image_buffer == NULL) {
        fprintf(stderr, "\nFailed to allocate memory for image buffer\n");
        exit(1);
    }
    // 1x1



    for (int y = 0; y < height; y++) {
        if (random_multiplier == true) {
            multiplier = (rand() % 11)/10.0f;
        } else {
            multiplier = 1.0f;
        }
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * 3; // Calculate index for RGB values
            image_buffer[index] = random_pixel(r, multiplier); // Red
            image_buffer[index + 1] = random_pixel(g, multiplier); // Green
            image_buffer[index + 2] = random_pixel(b, multiplier); // Blue
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
