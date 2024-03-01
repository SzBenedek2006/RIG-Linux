#include <stdbool.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>


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
        fprintf(log_file, "%s\n", text);

        //usleep(500000);
        //printf("\e[F\e[S\e[%d;%dH%s", writeCoordinate[0], writeCoordinate[1], text);
        //fflush(stdout);
        //incrementCounter(&writeCoordinate[0]);


    }
}

void printDebugPlusInt(char text[], int numVar){
    if (allowDebugInfo) {
        fprintf(log_file, "%s%d\n", text, numVar);
        //usleep(500000);
        //printf("\e[F\e[S\e[%d;%dH%s%d", writeCoordinate[0], writeCoordinate[1], text, numVar);
        //fflush(stdout);
        //incrementCounter(&writeCoordinate[0]);
    }
}

void printDebugPlusStr(char text[], char strVar[]){
    if (allowDebugInfo) {
        fprintf(log_file, "%s%s\n", text, strVar);
        //usleep(500000);
        //printf("\e[F\e[S\e[%d;%dH%s%s", writeCoordinate[0], writeCoordinate[1], text, strVar);
        //fflush(stdout);
        //incrementCounter(&writeCoordinate[0]);
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
