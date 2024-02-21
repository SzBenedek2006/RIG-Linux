#include <stdbool.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>


int writeCoordinate[2] = {0, 1};
bool allowDebugInfo = false;
unsigned short int terminalHeight = 0;
unsigned short int terminalWidth = 0;

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
        usleep(1000000);
        printf("\e[F\e[S\e[%d;%dH%s", writeCoordinate[0], writeCoordinate[1], text);
        fflush(stdout);
        incrementCounter(&writeCoordinate[0]);
    }
}

void printDebugPlusInt(char text[], int numVar){
    if (allowDebugInfo) {
        usleep(1000000);
        printf("\e[F\e[S\e[%d;%dH%s%d", writeCoordinate[0], writeCoordinate[1], text, numVar);
        fflush(stdout);
        incrementCounter(&writeCoordinate[0]);
    }
}

void printDebugPlusStr(char text[], char strVar[]){
    if (allowDebugInfo) {
        usleep(1000000);
        printf("\e[F\e[S\e[%d;%dH%s%s", writeCoordinate[0], writeCoordinate[1], text, strVar);
        fflush(stdout);
        incrementCounter(&writeCoordinate[0]);
    }
}

void printHelp() {
    printf("Hi, options are the following:\n    '-s' or '--size' <height "
               "width>\n    "
               "'-a' or '--alpha' (this toggles transparency in image formats that "
               "support it)\n    '-c' or '--count' <number>\n    "
               "'--termux-external' (uses your internal storage on android)\n    "
               "'-d' or '--debug' (print debug info)\n    '-h' or '--help' (this "
               "message)\n\n    Example: -s 10 20 -a -c 10\n");
}
