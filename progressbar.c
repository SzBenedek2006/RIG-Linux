#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
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
const long seconds_in_hour = 3600;
uint8_t counter = 0;

// Structs in header

struct Time convertSeconds(long total_seconds) {
    struct Time time;

    time.hours = total_seconds / seconds_in_hour;
    time.minutes = (total_seconds % seconds_in_hour) / 60;
    time.seconds = total_seconds % seconds_in_hour;

    return time; // you can return struct vars in c
}


void progressbar(int progress, int total, int length, double time, uint8_t counter) { // For single threaded use:






    long seconds = time;
    printDebugPlusInt("Seconds:", seconds);

    double milliseconds = time - seconds;

    struct Time realTime = convertSeconds(seconds); // Update eta before this point!!!

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
            printf("] %.0f%% eta: %02ld:%02ld:%02ld.%02d", progressPercent, realTime.hours, realTime.minutes, realTime.seconds, (int)(milliseconds*100)); // megcsinálni az eta számlálásst az új módszerrel
        }

        fflush(stdout);

    } else {
        progress_indicator();
    }
}

void* multiThreadedProgressbar(void* arg) {

    struct ProgressBarArgs *args = (struct ProgressBarArgs *)arg;
    progressbar(args->progress, args->total, args->length, args->time, counter);
    int progress_previous = 0;
    int progress_current = args->progress;
    int i = 0;
    while(1) {

        pthread_mutex_lock(&mutex);
        progress_previous = progress_current;
        progress_current = args->progress;

        if (i % 10000 == 0) {
            if (counter < 3) {
                (*(&counter))++;
            } else {
                *(&counter) = 0;
            }
        }


        if (progress_current > progress_previous) {
            progressbar(args->progress, args->total, args->length, args->time, counter);
            progress_previous = progress_current;
        }


        if (args->progress == args->total) {
            printDebugPlusInt("Time in loop: ", args->time);
            // If here happens an increment in progress, it breaks at 99%, even when using mutexes.
            progressbar(args->progress, args->total, args->length, args->time, counter);
            pthread_mutex_unlock(&mutex);
            break;
        }

        pthread_mutex_unlock(&mutex);
        fflush(stdout);
        i++;
        usleep(100);
    }


    return NULL;
}

void progress_indicator() {
    if (counter == 0) {
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
