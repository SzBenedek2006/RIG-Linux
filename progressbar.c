#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h> // Need to include here too.

#include "my_utils.c"


pthread_mutex_t mutex; // Declare global variable in a place that is accessible to both files.s


const unsigned short int needAveraging = 25; // Yeah, I'm bad at naming stuff

double time1 = 0;
double time2 = 0;
unsigned int tCounter = 1;
unsigned int eta = 0;

unsigned int eta0 = 0;
unsigned int eta1 = 0;
unsigned int eta2 = 0;
unsigned int eta3 = 0;
unsigned int eta4 = 0;
unsigned int eta5 = 0;
unsigned int eta6 = 0;
unsigned int eta7 = 0;
short unsigned int counter;

struct ProgressBarArgs {
        int progress;
        int total;
        int length;
        double time;
};



struct Time {
    int hours;
    int minutes;
    int seconds;
};

struct Time convertSeconds(int total_seconds) {
    struct Time time;

    time.hours = total_seconds / 3600; // Calculate hours
    time.minutes = (total_seconds % 3600) / 60; // Calculate minutes
    time.seconds = total_seconds % 60; // Calculate remaining seconds

    return time; // Return the struct with converted time values
}

void remainingTime(double time, double* time1, double* time2, unsigned int* tCounter, int total, int progress) {

    if (*tCounter == 1) {
        *time1 = time;
    } else {
        *time2 = time;
    }


    if (*time1 && *time2 != 0) {
        if (*tCounter == 1) {
            *(&eta) = (total - progress) * ((*time1) - (*time2));
        } else {
            *(&eta) = (total - progress) * ((*time2) - (*time1));
        }
    }



    if (*tCounter == 2) {
        *tCounter = 1;
    } else {
        *tCounter = 2;
    }
}



void progressbar(int progress, int total, int length, double time) { // For single threaded use:



    *(&counter) = (int)((float)progress / total * 100) % 4; // Counts 0 -> 3 without additional variable added


    struct Time realTime = convertSeconds(eta); // Update eta before this point!!!

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

        remainingTime(time, &time1, &time2, &tCounter, total, progress);

        // Don't print time if it is still calculating
        if (((progress == 1 || progress == 2) && total <= needAveraging) || ((progress == 1 || progress == 2 || progress == 3 || progress == 4 || progress == 5) && total >= needAveraging)) { // This is the first run
            printf("] %.0f%% eta: calc...", progressPercent);
        } else {
            printf("] %.0f%% eta: %02d:%02d:%02d", progressPercent, realTime.hours, realTime.minutes, realTime.seconds);
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


    // Separate the time calculation out of the progressbar


    struct ProgressBarArgs *args = (struct ProgressBarArgs *)arg;
    while(1) {
        pthread_mutex_lock(&mutex);

        printDebugPlusInt("Time before loop: ", args->time);
        progressbar(args->progress, args->total, args->length, args->time);
        // If here happens an increment in progress, it breaks at 99%, even when using mutexes.
        if (args->progress == args->total) {
            printDebugPlusInt("Time in loop: ", args->time);
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
