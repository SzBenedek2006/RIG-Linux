#include <png.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_utils.h"
#include "PNG_generator.h"


int generatePNG(const char *filename, unsigned int width, unsigned int height, bool alpha, bool allowDebugInfo, uint8_t r, uint8_t g, uint8_t b, bool random_multiplier) {

    float multiplier = 0.0f;

    // Initialize PNG structures and open a file for writing
  FILE *fp = fopen(filename, "wb");

  // Handle file opening error
  if (!fp) {
    printDebug("Error creating the image file. png error 1");
    return 1;
  }

  // Handle PNG structure creation error
  png_structp png_ptr =
      png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
    fclose(fp);

    printDebug("Error creating the image file. png error 2");
    return 2;
  }

  // Handle PNG info creation error
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    png_destroy_write_struct(&png_ptr, NULL);
    fclose(fp);
    printDebug("Error creating tunsigned inthe image file. png error 3");
    return 3;
  }

  printDebug("File created");

  png_init_io(png_ptr, fp);

  // Set up the image attributes

  // int width = 10;  // width of the image
  // int height = 10; // height of the image


  // Test alpha
  if (alpha == true) { // If alpha true run
    png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++) {
        if (random_multiplier == true) {
            multiplier = (rand() % 11)/10.0f;
        } else {
            multiplier = 1.0f;
        }

        row_pointers[y] = (png_byte *)malloc(4 * width); // 4 bytes per pixel (RGBA)
        for (int x = 0; x < width; x++) {
            row_pointers[y][4 * x] = random_pixel(r, multiplier);     // Red channel
            row_pointers[y][4 * x + 1] = random_pixel(g, multiplier); // Green channel
            row_pointers[y][4 * x + 2] = random_pixel(b, multiplier); // Blue channel
            row_pointers[y][4 * x + 3] = random_pixel(255, multiplier); // Alpha channel
        }
    }

    int color_type = PNG_COLOR_TYPE_RGBA;
    int bit_depth = 8;

    png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
               PNG_FILTER_TYPE_BASE);

    printDebug("IHDR set");

    png_set_rows(png_ptr, info_ptr, row_pointers);
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    for (int y = 0; y < height; y++) {
      free(row_pointers[y]);
    }
    free(row_pointers);

  } else { // If alpha false, run
    // Write the image data
    png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);

    for (int y = 0; y < height; y++) {
        if (random_multiplier == true) {
            multiplier = (rand() % 11)/10.0f;
        } else {
            multiplier = 1.0f;
        }

        //printf("multiplier: %f\n", multiplier);
        row_pointers[y] = (png_byte *)malloc(3 * width); // 3 bytes per pixel (RGB)
        for (int x = 0; x < width; x++) {
            row_pointers[y][3 * x] = random_pixel(r, multiplier); printDebugPlusInt("r:", r);     // Red channel
            row_pointers[y][3 * x + 1] = random_pixel(g, multiplier); printDebugPlusInt("g:", g);   // Green channel
            row_pointers[y][3 * x + 2] = random_pixel(b, multiplier); printDebugPlusInt("g:", b);   // Blue channel
        }
    }

    int color_type = PNG_COLOR_TYPE_RGB;
    int bit_depth = 8;

    png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
               PNG_FILTER_TYPE_BASE);

    printDebug("IHDR set");

    png_set_rows(png_ptr, info_ptr, row_pointers);
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    for (int y = 0; y < height; y++) {
      free(row_pointers[y]);
    }
    free(row_pointers);
  }


  printDebug("File freed");


  // Clean up and close the file
  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(fp);


  printDebug("File closed");


  return 0;
}
