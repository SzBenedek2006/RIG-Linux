#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <math.h>
#include "my_utils.h"


#define COLOR_BOLD  "\e[1m"
#define COLOR_OFF   "\033[m"

#define BOLD(x) "\e[1m"x"\033[m"


// Global vars
struct timespec ts;
double startTime;
double *pStartTime = &startTime;
int writeCoordinate[2] = {0, 1};
bool allowDebugInfo = false;
unsigned short int terminalHeight = 0;
unsigned short int terminalWidth = 0;
FILE *log_file;

uint32_t rand32_state;

// 8bit XOR + bitshift random function based on George Marsaglia's work and gpt-4o.
static inline uint8_t rand8_xorshift(void) {
    rand32_state ^= rand32_state << 13;
    rand32_state ^= rand32_state >> 17;
    rand32_state ^= rand32_state << 5;
    return (uint8_t)rand32_state;
}

int errorFileOpener() {
    if (allowDebugInfo) {
         // Declare a file pointer
        char data[100]; // Data to write to the file

        // Open file in write mode. If the file doesn't exist, it will be created.
        // If the file exists, its contents will be overwritten.
        log_file = fopen("log.txt", "w");

        if (log_file == NULL) { // Check if the file was opened successfully
            printf("Error opening the file.\n");
            return 1;
        }
    }
    return 0;
}


int errorFileCloser() {
    if (allowDebugInfo) {
        fclose(log_file);
    }
    return 0;
}


void incrementCounter(int *ptr) {
    if ((*ptr) > terminalHeight - 2) {
            (*ptr) = 1;
        }
}



void getTerminalSize(unsigned short int* rows, unsigned short int* cols)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *rows = w.ws_row;
    *cols = w.ws_col;
}

// WIP
// Replacing if (allowDebugInfo) mess with a cleaner approach
void printDebug(char text[]) {
    if (allowDebugInfo) {
        clock_gettime(CLOCK_REALTIME, &ts);
        double msgTime =( (double)ts.tv_sec + (double)ts.tv_nsec / 1.0e9 ) - *pStartTime;
        fprintf(log_file, "%lf: %s\n", msgTime, text);
    }
}

void printDebugPlusInt(char text[], int numVar){
    if (allowDebugInfo) {
        clock_gettime(CLOCK_REALTIME, &ts);
        double msgTime =( (double)ts.tv_sec + (double)ts.tv_nsec / 1.0e9 ) - *pStartTime;
        fprintf(log_file, "%lf: %s %d\n", msgTime, text, numVar);
    }
}

void printDebugPlusFloat(char text[], double flVar){
    if (allowDebugInfo) {
        clock_gettime(CLOCK_REALTIME, &ts);
        double msgTime =( (double)ts.tv_sec + (double)ts.tv_nsec / 1.0e9 ) - *pStartTime;
        fprintf(log_file, "%lf: %s %lf\n", msgTime, text, flVar);
    }
}

void printDebugPlusStr(char text[], char strVar[]){
    if (allowDebugInfo) {
        clock_gettime(CLOCK_REALTIME, &ts);
        double msgTime =( (double)ts.tv_sec + (double)ts.tv_nsec / 1.0e9 ) - *pStartTime;
        fprintf(log_file, "%lf: %s %s\n", msgTime, text, strVar);
    }
}



void printHelp() {
    system("clear");
    printf( "Random Image Generator %s.\n"
            "Project website: https://github.com/SzBenedek2006/RIG-Linux\n"
            "My website (^-^): https://szbenedek2006.me\n"
            "\n"
            "\n"
            "RIG options:\n"
            "\n"
            "    " BOLD("-s") " or " BOLD("--size") " <width height>\n"
            "    Changed the order in 2.0!\n"
            "\n"
            "    " BOLD("-c") " or " BOLD("--count") " <number>\n"
            "    This many images will be generated.\n"
            "\n"
            "    " BOLD("-f") " or " BOLD("--format") " <image format>\n"
            "    It supports png or jpg (jpeg) formats. When not used, defaults to png.\n"
            "\n"
            "    " BOLD("-a") " or " BOLD("--alpha") "\n"
            "    Use transparent pixels in png. With jpeg, this will be ignored.\n"
            "\n"
            "    " BOLD("--termux-external") "\n"
            "    When used in Termux, images will be moved to your internal storage.\n"
            "\n"
            "    " BOLD("-d") " or " BOLD("--debug") "\n"
            "    Print debug info.\n"
            "\n"
            "    " BOLD("--rgb") " or " BOLD("--RGB") " <RED GREEN BLUE>\n"
            "    This sets the values in each channel, so you can make colorful or darker images.\n"
            "\n"
            "    " BOLD("--sensor-noise") "\n"
            "    Puts lines on the pictures, like image sensors with high iso.\n"
            "\n"
            "    " BOLD("-h") " or " BOLD("--help") "\n"
            "    Prints this message to console.\n"
            "\n"
            "Example:\n"
            "    -s 10 20 -a -c 10 -f png\n", RIG_VERSION);
}

uint8_t random_pixel(uint8_t max_value, float multiplier) {
    //printf("\nmao\n");
    uint8_t pixel = 0;
    if (max_value == 0) {
        return pixel;
    }
    if (multiplier < 0.1) {
        multiplier = 1.0;
    }
    if (multiplier < 0.2) {
        multiplier = 0.3;
    }
    if (multiplier < 0.3) {
        multiplier = 0.5;
    }
    multiplier = sqrt(multiplier);
    //pixel = rand() % (uint16_t)roundf((max_value + 1) * multiplier);
    pixel = rand8_xorshift() % (uint16_t)(max_value + 1) * multiplier;

    //printDebugPlusInt("Max value:", max_value);
    //printDebugPlusFloat("Multiplier:", multiplier); //printf("Multiplier: %lf\n", multiplier);
    //printDebugPlusInt("Pixel:", pixel);
    return pixel;
}
