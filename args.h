#ifndef ARGS
#define ARGS
#include <stdbool.h>
#include <stdint.h>

struct Counts {
    short unsigned int sCount;      // -s, --size
    short unsigned int cCount;      // -c --count
    short unsigned int aCount;      // -a --alpha
    short unsigned int hCount;      // -h --help
    short unsigned int tCount;      // --termux_external
    short unsigned int dCount;      // -d --debug
    short unsigned int fCount;      // -f --format
    short unsigned int qCount;      // -q --quality
    short unsigned int rgbCount;    // --rgb --RGB
    short unsigned int snCount;     // --sensor-noise
};

int args(
    int argc,
    char* argv[],
    struct Counts* counts,
    unsigned int* width,
    unsigned int* height,
    bool* alpha,
    unsigned int* count,
    bool* help,
    bool* termuxExternal,
    bool* random_multiplier,
    uint8_t* quality,
    uint8_t* r,
    uint8_t* g,
    uint8_t* b,
    char* format
);


#endif
