#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>

#include "version.c"

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
    printf( "Hi! This is Random Image Generator (RIG) %s.\n"
            "Project website: https://github.com/SzBenedek2006/RIG-Linux\n"
            "My website (^-^): https://szbenedek2006.me\n\n\n"


            "RIG options:\n\n"

            "Size (width x height):\n"
            "    '-s' or '--size' <width height>\n"
            "    (changed the order in 2.0)\n"
            "Count:\n"
            "    '-c' or '--count' <number>\n"
            "Format:\n"
            "    '-f' or '--format' 'png' or 'jpg'\n"
            "    (When not used, defaults to png.)\n"
            "Transparency:\n"
            "    '-a' or '--alpha'\n"
            "    (use transparent pixels in png. with jpg, this will be ignored)\n"
            "Make images accessible out of termux:\n"
            "    '--termux-external'\n"
            "    (when used in Termux, images will be moved to your internal storage)\n"
            "Print debug info to a log file"
            "    '-d' or '--debug'\n"
            "    (print debug info)\n"
            "Help message"
            "    '-h' or '--help'\n"
            "    (prints this message to console)\n\n"

            "    Example: -s 10 20 -a -c 10 -f png\n", VERSION);
}







