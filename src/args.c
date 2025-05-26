#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "args.h"
#include "my_utils.h"




int n;

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
) {
    int temp = 0;

    for (n = 1; n < argc; n++) {
        if (strcmp(argv[n], "-s") == 0 || strcmp(argv[n], "--size") == 0) { // -s,
            (counts->sCount)++;
            if (argv[n + 1] != NULL && argv[n + 1] != NULL) {
                    *width = atoi(argv[n + 1]);
                    *height = atoi(argv[n + 2]);
                    n += 2;
            } else {
                printf("Size is not specified!\n");
                return 3;
            }
        } else if (strcmp(argv[n], "-a") == 0 || strcmp(argv[n], "--alpha") == 0) { // If n-th arg        -a,
            *alpha = true;
            counts->aCount++;
        } else if (strcmp(argv[n], "-c") == 0 || strcmp(argv[n], "--count") == 0) { // If n-th arg      -c,
            if (argv[n + 1] != NULL) {
                *count = atoi(argv[n + 1]);
                counts->cCount++;
                n++;
            } else {
                printf("Count is not specified!\n");
                return 3;
            }
        } else if (strcmp(argv[n], "-h") == 0 || strcmp(argv[n], "--help") == 0) { // If n-th arg       -h,
            *help = true;
            counts->hCount++;
        } else if (strcmp(argv[n], "--termux-external") == 0) { // If n-th arg -a,
            *termuxExternal = true; // to implement
            counts->tCount++; // to implement
        } else if (strcmp(argv[n], "-d") == 0 || strcmp(argv[n], "--debug") == 0) { // If n-th arg -a,
            allowDebugInfo = true; // to implement
            counts->dCount++; // to implement
        } else if (strcmp(argv[n], "-f") == 0 || strcmp(argv[n], "--format") == 0) { // If n-th arg -f
            counts->fCount++;
            if ((argv[n + 1]) != NULL) {
                if (strcmp(argv[n + 1], "png") == 0) {
                    strcpy(format, "png");
                    n++;
                } else if (strcmp(argv[n + 1], "jpeg") == 0 || strcmp(argv[n + 1], "jpg") == 0) {
                    strcpy(format, "jpg");
                    n++;
                 } else {
                    printf("RIG currently only supports png (default) and jpeg as a format option!");
                    return 3;
                 }
            } else {
                printf("--format/-f is not set correctly or left empty, write image format after -f or --format!\n");
                return 3;
            }
        } else if (strcmp(argv[n], "-q") == 0 || strcmp(argv[n], "--quality") == 0) { // If n-th arg -q
            counts->qCount++;
            if ((argv[n + 1]) != NULL) {
                *quality = atoi(argv[n + 1]);
                if (*quality > 0 && *quality <= 100) {
                    n++;
                } else {
                    printf("Quality isn't set correctly!\n");
                    return 3;
                }
            } else {
                printf("Missing quality value after -q or --quality.\n");
                return 3;
            }
        } else if (strcmp(argv[n], "--rgb") == 0 || strcmp(argv[n], "--RGB") == 0) {
            if ((argv[n + 1]) != NULL) {
                temp = atoi(argv[n + 1]);
                if (temp <= 255 && r >= 0) {
                    *r = temp;
                } else {
                    printf("Red value is outside of the range (0-255)!\n");
                    return 3;
                }
            } else {
                printf("Red value missing!\n");
                return 3;
            }
            if ((argv[n + 2]) != NULL) {
                temp = atoi(argv[n + 2]);
                if (temp <= 255 && g >= 0) {
                    *g = temp;
                } else {
                    printf("Green value is outside of the range (0-255)!\n");
                    return 3;
                }
            } else {
                printf("Green value missing!\n");
                return 3;
            }
            if ((argv[n + 3]) != NULL) {
                temp = atoi(argv[n + 3]);
                if (temp <= 255 && b >= 0) {
                    *b = temp;
                } else {
                    printf("Blue value is outside of the range (0-255)!\n");
                    return 3;
                }
            } else {
                printf("Blue value missing!\n");
                return 3;
            }
            n += 3;
        } else if (strcmp(argv[n], "--sensor-noise") == 0) {
            *random_multiplier = true;
        } else { // If there is no known argument at a given argc location.
            printf("Unknown option \"%s\" at the %d. argument. Use -h for help.\n", argv[n], n);
            return 3;
        }
    }
    return 0;
}
