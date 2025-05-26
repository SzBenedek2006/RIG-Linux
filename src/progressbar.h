#ifndef PROGRESSBAR
#define PROGRESSBAR

#include <stdint.h>
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
extern uint8_t counter;

struct ProgressBarArgs {
    int progress;
    int total;
    int length;
    double time;
};



struct Time {
    long hours;
    long minutes;
    long seconds;
};

struct Time convertSeconds(long total_seconds);

void progressbar(int progress, int total, int length, double time, uint8_t counter);

void* multiThreadedProgressbar(void* arg);
void progress_indicator();


#endif
