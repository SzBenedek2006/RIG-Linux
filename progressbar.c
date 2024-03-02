#include <stdio.h>
#include <unistd.h>

double eta = 10;
double *pEta = &eta;



void progressbar(int progress, int total, int length, double *time) {
    short unsigned int dotcounter = progress % 4; // Counts 0 -> 3 without additional variable added
    
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
}
