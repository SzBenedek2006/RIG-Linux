#ifndef JPEG_GENERATOR
#define JPEG_GENERATOR
#include <stdint.h>

void generateJPEG(char *filename, long width, long height, int quality, uint8_t r, uint8_t g, uint8_t b, bool random_multiplier);
#endif // JPEG_GENERATOR
