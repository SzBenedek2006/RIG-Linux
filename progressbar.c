#include "my_utils.c" // Include only once
#include <stdio.h>
#include <unistd.h>

double time1 = 0;

double time2 = 0;

unsigned int tCounter = 1;

int eta = 0;
int* pEta = &eta;

struct Time {
    int hours;
    int minutes;
    int seconds;
};

struct Time convertSeconds(int total_seconds)
{
    struct Time time;

    time.hours = total_seconds / 3600; // Calculate hours
    time.minutes = (total_seconds % 3600) / 60; // Calculate minutes
    time.seconds = total_seconds % 60; // Calculate remaining seconds

    return time; // Return the struct with converted time values
}

void remainingTime(double time, double* time1, double* time2, unsigned int* tCounter, int total, int progress)
{

    if (*tCounter == 1) {
        *time1 = time;
    } else {
        *time2 = time;
    }

    // printf("\n %lf, %lf, %d, %lf\n");
    printDebugPlusInt("*time1 = ", *time1);
    printDebugPlusInt("*time2 = ", *time2);

    if (*time1 && *time2 != 0) {
        if (*tCounter == 1) {
            *pEta = (total - progress) * ((*time1) - (*time2)); // pEta?
        } else {
            *pEta = (total - progress) * ((*time2) - (*time1)); // pEta?
        }
    }
    (*tCounter)++;

    printDebugPlusInt("(*time2) - (*time1) = ", (*time2) - (*time1));

    if (*tCounter == 3) {
        *tCounter = 1;
    }
}

void progressbar(int progress, int total, int length, double time)
{
    short unsigned int dotcounter = progress % 4; // Counts 0 -> 3 without additional variable added

    struct Time realTime = convertSeconds(eta);

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
        printf("] %.0f%% eta: %d:%d:%d", progressPercent, realTime.hours, realTime.minutes, realTime.seconds);
        fflush(stdout);

    } else if (dotcounter == 0) {
        printf("\r\033[K");
        printf("Generating images");
        fflush(stdout);

    } else if (dotcounter == 1) {
        printf("\r\033[K");
        printf("Generating images.");
        fflush(stdout);

    } else if (dotcounter == 2) {
        printf("\r\033[K");
        printf("Generating images..");
        fflush(stdout);

    } else {
        printf("\r\033[K");
        printf("Generating images...");
        fflush(stdout);
    }
}
