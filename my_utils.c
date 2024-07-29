#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include "my_utils.h"


#define COLOR_BOLD  "\e[1m"
#define COLOR_OFF   "\033[m"


// Global vars
struct timespec ts;
double startTime;
double *pStartTime = &startTime;
int writeCoordinate[2] = {0, 1};
bool allowDebugInfo = false;
unsigned short int terminalHeight = 0;
unsigned short int terminalWidth = 0;
FILE *log_file;


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
        fprintf(log_file, "%lf: %s%d\n", msgTime, text, numVar);
    }
}

void printDebugPlusFloat(char text[], double flVar){
    if (allowDebugInfo) {
        clock_gettime(CLOCK_REALTIME, &ts);
        double msgTime =( (double)ts.tv_sec + (double)ts.tv_nsec / 1.0e9 ) - *pStartTime;
        fprintf(log_file, "%lf: %s%lf\n", msgTime, text, flVar);
    }
}

void printDebugPlusStr(char text[], char strVar[]){
    if (allowDebugInfo) {
        clock_gettime(CLOCK_REALTIME, &ts);
        double msgTime =( (double)ts.tv_sec + (double)ts.tv_nsec / 1.0e9 ) - *pStartTime;
        fprintf(log_file, "%lf: %s%s\n", msgTime, text, strVar);
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
            "    "COLOR_BOLD "-s" COLOR_OFF " or "COLOR_BOLD "--size" COLOR_OFF " <width height>\n" // "COLOR_BOLD "" COLOR_OFF "
            "    Changed the order in 2.0!\n"
            "\n"
            "    "COLOR_BOLD "-c" COLOR_OFF " or "COLOR_BOLD "--count" COLOR_OFF " <number>\n"
            "\n"
            "    "COLOR_BOLD "-f" COLOR_OFF " or "COLOR_BOLD "--format" COLOR_OFF " <image format>\n"
            "    It supports png or jpg (jpeg) formats. When not used, defaults to png.\n"
            "\n"
            "    "COLOR_BOLD "-a" COLOR_OFF " or "COLOR_BOLD "--alpha" COLOR_OFF "\n"
            "    Use transparent pixels in png. With jpeg, this will be ignored.\n"
            "\n"
            "    "COLOR_BOLD "--termux-external" COLOR_OFF "\n"
            "    When used in Termux, images will be moved to your internal storage.\n"
            "\n"
            "    "COLOR_BOLD "-d" COLOR_OFF " or "COLOR_BOLD "--debug" COLOR_OFF "\n"
            "    Print debug info.\n"
            "\n"
            "    "COLOR_BOLD "-h" COLOR_OFF " or "COLOR_BOLD "--help" COLOR_OFF "\n"
            "    Prints this message to console.\n"
            "\n"
            "Example:\n"
            "    -s 10 20 -a -c 10 -f png\n", RIG_VERSION);
}
