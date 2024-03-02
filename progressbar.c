#include <stdio.h>
#include <unistd.h>
#include "my_utils.c" // Include only once



double time1 = 0;
double *pTime1 = &time1;

double time2 = 0;
double *pTime2 = &time2;

unsigned int tCounter = 0;
unsigned int *pTCounter = & tCounter;

double eta = 0;
double *pEta = &eta;



void progressbar(int progress, int total, int length, double time) {
    short unsigned int dotcounter = progress % 4; // Counts 0 -> 3 without additional variable added
    
    if (*pTCounter == 1) {
        *pTime1 = time;
    } else {
        *pTime2 = time;
    }



    *pEta = (total - progress) * ((*pTime2) - (*pTime1));
    printDebugPlusInt("(*pTime2) - (*pTime1) = ", (*pTime2) - (*pTime1));
    (*pTCounter)++;





    if (*pTCounter == 3) {
        *pTCounter = 0;
    }

    if (length >= 30) {
            
        int j;
        float progressPercent = (float) progress / total * 100;
        
        printf("\r\033[KProgress: [");
        for (j = 0; j < length; j++) {
            if (j < progressPercent * length / 100) {
                printf("■");
            } else {
                printf(" ");
            }
        }
        printf("] %.0f%% Time remaining: %lf", progressPercent, *pEta);
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

    //Random usleep jumpscare
    usleep(10000);
}
