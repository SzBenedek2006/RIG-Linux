#include "my_utils.c" // Include only once
#include <stdio.h>
#include <unistd.h>

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

// somehow update the ints separately based on the counter



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

    // Latest stuff... first 3 time incorrect
    if (total <= needAveraging) {
        if (*time1 && *time2 != 0) {
            if (*tCounter == 1) {
                *(&eta) = (total - progress) * ((*time1) - (*time2));
            } else {
                *(&eta) = (total - progress) * ((*time2) - (*time1));
            }
        }
    } else if (counter == 0) {
        if (*time1 && *time2 != 0) {
            if (*tCounter == 1) {
                *(&eta0) = (total - progress) * ((*time1) - (*time2));
            } else {
                *(&eta0) = (total - progress) * ((*time2) - (*time1));
            }
            *(&eta) = *(&eta0); // average calc
        }
    } else if (counter == 1) {
        if (*time1 && *time2 != 0) {
            if (*tCounter == 1) {
                *(&eta1) = (total - progress) * ((*time1) - (*time2));
            } else {
                *(&eta1) = (total - progress) * ((*time2) - (*time1));
            }
            *(&eta) = (*(&eta0) + *(&eta1)) / 2; // average calc
        }
    } else if (counter == 2) {
        if (*time1 && *time2 != 0) {
            if (*tCounter == 1) {
                *(&eta2) = (total - progress) * ((*time1) - (*time2));
            } else {
                *(&eta2) = (total - progress) * ((*time2) - (*time1));
            }
            *(&eta) = (*(&eta0) + *(&eta1) + *(&eta2)) / 3; // average calc
        }
    } else if (counter == 3) {
        if (*time1 && *time2 != 0) {
            if (*tCounter == 1) {
                *(&eta3) = (total - progress) * ((*time1) - (*time2));
            } else {
                *(&eta3) = (total - progress) * ((*time2) - (*time1));
            }
            *(&eta) = (*(&eta0) + *(&eta1) + *(&eta2) + *(&eta3)) / 4; // average calc
        }
    } else if (counter == 4) {
        if (*time1 && *time2 != 0) {
            if (*tCounter == 1) {
                *(&eta4) = (total - progress) * ((*time1) - (*time2));
            } else {
                *(&eta4) = (total - progress) * ((*time2) - (*time1));
            }
            *(&eta) = *(&eta0); // average calc
        }
    } else if (counter == 5) {
        if (*time1 && *time2 != 0) {
            if (*tCounter == 1) {
                *(&eta5) = (total - progress) * ((*time1) - (*time2));
            } else {
                *(&eta5) = (total - progress) * ((*time2) - (*time1));
            }
            *(&eta) = (*(&eta0) + *(&eta1)) / 2; // average calc
        }
    } else if (counter == 6) {
        if (*time1 && *time2 != 0) {
            if (*tCounter == 1) {
                *(&eta6) = (total - progress) * ((*time1) - (*time2));
            } else {
                *(&eta6) = (total - progress) * ((*time2) - (*time1));
            }
            *(&eta) = (*(&eta0) + *(&eta1) + *(&eta2)) / 3; // average calc
        }
    } else if (counter == 7) {
        if (*time1 && *time2 != 0) {
            if (*tCounter == 1) {
                *(&eta7) = (total - progress) * ((*time1) - (*time2));
            } else {
                *(&eta7) = (total - progress) * ((*time2) - (*time1));
            }
            *(&eta) = (*(&eta0) + *(&eta1) + *(&eta2) + *(&eta3)) / 4; // average calc
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

    *(&counter) = progress % 4; // Counts 0 -> 3 without additional variable added


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
