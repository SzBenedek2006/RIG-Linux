#ifndef MY_UTILS
#define MY_UTILS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <math.h>

#include "version.h"
#include "../stb/stb_image_write.h"

#define COLOR_BOLD  "\e[1m"
#define COLOR_OFF   "\033[m"

extern uint32_t rand32_state;

// Global vars
extern struct timespec ts;
extern double startTime;
extern double *pStartTime;

extern int writeCoordinate[2];
extern bool allowDebugInfo;
extern unsigned short int terminalHeight;
extern unsigned short int terminalWidth;
extern FILE *log_file;

// Function prototypes
int errorFileOpener();
int errorFileCloser();
void incrementCounter(int *ptr);
void getTerminalSize(unsigned short int* rows, unsigned short int* cols);
void printDebug(char text[]);
void printDebugPlusInt(char text[], int numVar);
void printDebugPlusFloat(char text[], double flVar);
void printDebugPlusStr(char text[], char strVar[]);
void printHelp();
uint8_t random_pixel(uint8_t max_value, float multipier);
int set_affinity(int core_id);
unsigned char* generatePixelMapData(unsigned int width, unsigned int height, bool alpha, uint8_t r, uint8_t g, uint8_t b, bool random_multiplier);

#endif
