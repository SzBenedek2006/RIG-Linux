#include "dir_creator.h"
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_utils.h"
#include <stdbool.h>

static int termux_setup_storage = false;

bool check_access_termux () {
    if (access(androidInternalPath, W_OK) == 0)
    return true;
    else
    return false;
}

int termuxPermissionNeeded = 0; //TODO: replace this with a function
char androidInternalPath[] = "/storage/emulated/0/";

int dirCreatorLinux(char dirName[], bool isTermux) { // Starting of the function

    mkdir(dirName, 0700);

    if (isTermux == false) {

        DIR *dir = opendir(dirName); // dir = dirName.

        printDebug("Dir struct created");

        if (dir != NULL) {
            printDebug("Output directory created");
            closedir(dir);              // Close dir!
            return 0;                   // Return directory exists.
        } else if (ENOENT == errno) { // If dir not exists
            printDebug("Output directory doesn't exist");
            return 1;                   // Return directory does not exist.
        } else {                      // If other fail
            printDebug("Output directory may or may not exist");
            return 2; // Return opendir() failed for some other reason.
        }
    } else {
        termuxPermissionNeeded = access(androidInternalPath, W_OK);
        printDebugPlusInt("check_access_termux():", check_access_termux());
        int rounds = 0;
        printf("Termux needs storage permission. Press allow in the following screen.\n");
        while (!check_access_termux()) {
            rounds++;
            sleep(1);
            system("termux-setup-storage");
            printf("Waiting %d seconds before retrying\n", rounds);
            sleep(rounds);
            termuxPermissionNeeded = access(androidInternalPath, W_OK);
            if (!check_access_termux()) {
                printDebugPlusInt("Error Number : %d\n", errno);
                perror("Error");
                printf("Retry\n");
            }
        }


        //This part is the original, doing the same thing as the non termux part
        strcat(androidInternalPath, dirName);
        DIR *dir = opendir(androidInternalPath); // androidInternalPath should now be the dir where pics will be placed.

        if (dir) { // If dir exists

            closedir(dir);
            // Close dir!
            return 0;                   // Return directory exists.
        } else if (ENOENT == errno) { // If dir not exists
            return 1;                   // Return directory does not exist.

        } else {    // If other fail
            return 2; // Return opendir() failed for some other reason.
        }
    }
}

// Megcsinálni a termux-setup-storage-t
