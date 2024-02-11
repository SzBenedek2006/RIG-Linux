#include <stdio.h>
#include <unistd.h>

void progressbar(int progress, int total, int length) {
    int j;
    float progressPercent = (float) progress / total * 100;
    printf("Progress: [");
    for (j = 0; j < length; j++) { // a középső szám állítja a vonal hosszúgágát
        if (j < progressPercent * length / 100) {
            printf("■");
        } else {
            printf(" ");
        }
    }
    printf("] %.0f%%\r", progressPercent);
    fflush(stdout);
}
