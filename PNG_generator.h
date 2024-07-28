#ifndef PNG_GENERATOR
#define PNG_GENERATOR

#include <stdbool.h>

int generatePNG(const char *filename, unsigned int width, unsigned int height, bool alpha, bool allowDebugInfo);

#endif
