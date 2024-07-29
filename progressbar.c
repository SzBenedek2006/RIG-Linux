#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "my_utils.h"
#include "progressbar.h"


pthread_mutex_t mutex;

unsigned short int needAveraging = 25;
double time1 = 0;
double time2 = 0;
unsigned int tCounter = 1;
short unsigned int counter;

// Structs in header

struct Time convertSeconds(int total_seconds) {
    struct Time time;

    time.hours = total_seconds / 3600;
    time.minutes = (total_seconds % 3600) / 60;
    time.seconds = total_seconds % 60;

    return time; // you can return struct vars in c
}


void progressbar(int progress, int total, int length, double time) { // For single threaded use:



    // *(&counter) = (int)((float)progress / total * 100) % 4; // Counts 0 -> 3 without additional variable added
    //
    //
    struct Time realTime = convertSeconds(time); // Update eta before this point!!!

    if (length >= 30) {

        int j;
        float progressPercent = (float)progress / total * 100;

        printf("\r\033[KProgress: [");
        for (j = 0; j < length; j++) {
            if (j < progressPercent * length / 100) {
                printf("■");
            } else {
                printf(" ");
            }
        }


        // At first run, time can't be calculated, so don't display it.
        if (progress == 1) {
            printf("] %.0f%%", progressPercent);
        } else {
            printf("] %.0f%% eta: %02d:%02d:%02d", progressPercent, realTime.hours, realTime.minutes, realTime.seconds); // megcsinálni az eta számlálásst az új módszerrel
        }

        fflush(stdout);

    } else if (counter == 0) {
        printf("\r\033[K");
        printf("Generating images");
        fflush(stdout);

    } else if (counter == 1) {
        printf("\r\033[K");
        printf("Generating images.");
        fflush(stdout);

    } else if (counter == 2) {
        printf("\r\033[K");
        printf("Generating images..");
        fflush(stdout);

    } else {
        printf("\r\033[K");
        printf("Generating images...");
        fflush(stdout);
    }
}

void* multiThreadedProgressbar(void* arg) {

    struct ProgressBarArgs *args = (struct ProgressBarArgs *)arg;
    progressbar(args->progress, args->total, args->length, args->time);
    int progress_previous = 0;
    int progress_current = args->progress;
    while(1) {
        pthread_mutex_lock(&mutex);
        progress_previous = progress_current;
        progress_current = args->progress;

        if (progress_current > progress_previous) {
            progressbar(args->progress, args->total, args->length, args->time);
            progress_previous = progress_current;
        }


        if (args->progress == args->total) {
            printDebugPlusInt("Time in loop: ", args->time);
            // If here happens an increment in progress, it breaks at 99%, even when using mutexes.
            progressbar(args->progress, args->total, args->length, args->time);
            pthread_mutex_unlock(&mutex);
            break;
        }

        pthread_mutex_unlock(&mutex);
        fflush(stdout);
        usleep(100);
    }


    return NULL;
}
