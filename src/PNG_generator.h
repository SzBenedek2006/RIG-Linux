#ifndef PNG_GENERATOR
#define PNG_GENERATOR

#include <stdbool.h>
#include <stdint.h>

int generatePNG(const char *filename, unsigned int width, unsigned int height, bool alpha, bool allowDebugInfo, uint8_t r, uint8_t g, uint8_t b, bool random_multiplier);
int generatePNG2(const char *filename, unsigned int width, unsigned int height, bool alpha, bool allowDebugInfo, uint8_t r, uint8_t g, uint8_t b, bool random_multiplier);

#endif
