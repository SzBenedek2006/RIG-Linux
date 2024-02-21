#include <stdbool.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>



bool allowDebugInfo = false;


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
        printf("\033[A\033[A%s\n\033[B", text);
        fflush(stdout);
    }
}

void printDebugPlusInt(char text[], int numVar){
    if (allowDebugInfo) {
        usleep(1000000);
        printf("\033[A\033[A%s%d\n\033[B", text, numVar);
        fflush(stdout);
    }
}

void printDebugPlusStr(char text[], char strVar[]){
    if (allowDebugInfo) {
        usleep(1000000);
        printf("\033[A\033[A%s%s\n\033[B", text, strVar);
        fflush(stdout);
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
