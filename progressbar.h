#ifndef PROGRESSBAR
#define PROGRESSBAR

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "my_utils.h"

extern pthread_mutex_t mutex;
extern unsigned short int needAveraging;

extern double time1;
extern double time2;
extern unsigned int tCounter;
extern short unsigned int counter;

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

struct Time convertSeconds(int total_seconds);

void progressbar(int progress, int total, int length, double time);

void* multiThreadedProgressbar(void* arg);


#endif
