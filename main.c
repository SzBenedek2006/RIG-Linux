#include "PNG_generator.c"
#include "dir_creator.c"

// my_utils.c is included in PNG_generator.c

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>


const int MS = 1000;

int main(int argc, char* argv[])
{

    // Get the current time in UTC
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        perror("clock_gettime");
        return 1;
    }

    *pStartTime = (double)ts.tv_sec + (double)ts.tv_nsec / 1.0e9;

    // system("clear");
    printf("Welcome to RIG\n");

    // Declaring vars
    unsigned int width = 0;
    unsigned int height = 0;
    bool alpha = false;
    unsigned int count;
    int n;
    bool help = false;
    bool termuxExternal = false;
    char outDir[] = "out";
    char outDirTermux[] = "/storage/emulated/0/";
    int termuxPermissionNeeded = 0;

    // Terminal sizes:

    getTerminalSize(&terminalHeight, &terminalWidth);

    /*for (int i = 0; i < terminalHeight - 3; i++) {
     *   printf("\n");
    }*/

    // Number of the same arguments
    short unsigned int sCount = 0; // -s, --size
    short unsigned int cCount = 0; // -c --count
    short unsigned int aCount = 0; // -a --alpha
    short unsigned int hCount = 0; // -h --help
    short unsigned int tCount = 0; // --termux_external
    short unsigned int dCount = 0; // -d --debug

    // Print the arguments
    // for (int i = 0; i <= argc+1; i++) {
    //  printf("Argv%d = %s\n", i, argv[i]);
    //}

    // Handle the arguments.
    for (n = 1; n < argc; n++) {
        if (strcmp(argv[n], "-s") == 0 || strcmp(argv[n], "--size") == 0) { // -s,
            sCount++;
            if (argv[n + 1] != NULL) {
                if (atoi(argv[n + 1]) >= 0) {
                    height = atoi(argv[n + 1]);
                }
            } else {
                printf("size is not set\n");
                return 2;
            }
            if (atoi(argv[n + 2]) >= 0) {
                width = atoi(argv[n + 2]);
            } else {
                printf("size is not set\n");
                return 2;
            }
        } else if (strcmp(argv[n], "-a") == 0 || strcmp(argv[n], "--alpha") == 0) { // If n-th arg        -a,
            alpha = true;
            aCount++;
        } else if (strcmp(argv[n], "-c") == 0 || strcmp(argv[n], "--count") == 0) { // If n-th arg      -c,
            if (argv[n + 1] != NULL) {
                count = atoi(argv[n + 1]);
                cCount++;
            } else {
                printf("count is not set\n");
                return 3;
            }

        } else if (strcmp(argv[n], "-h") == 0 || strcmp(argv[n], "--help") == 0) { // If n-th arg       -h,
            help = true;
            hCount++;
        } else if (strcmp(argv[n], "--termux-external") == 0) { // If n-th arg -a,
            termuxExternal = true; // to implement
            tCount++; // to implement
        } else if (strcmp(argv[n], "-d") == 0 || strcmp(argv[n], "--debug") == 0) { // If n-th arg -a,
            allowDebugInfo = true; // to implement
            dCount++; // to implement
        }
    }
    errorFileOpener();

    printDebugPlusInt("sCount = ", sCount);
    printDebugPlusInt("aCount = ", aCount);
    printDebugPlusInt("cCount = ", cCount);
    printDebugPlusInt("hCount = ", hCount);

    if (argc == 1) {
        printf("Use -h to print help message.\n");
        return 0;
    }

    // Too few arguments warning
    if ((width == 0 || height == 0 || count == 0) && !help) {
        printf("Too few arguments. Width, height or count is 0. Unexpected "
               "behaviour may occur! (Argc = %d)\n",
            argc);
        return 1;
    }

    // Too many arguments
    if (sCount > 1 || cCount > 1 || aCount > 1 || hCount > 1 || tCount > 1) {
        printf("Too many arguments in the same type.");
        return 1;
    }

    // Helpmsg
    if (help == true) {
        printHelp();
        return 0;
    }

    if (!termuxExternal) {
        dirCreatorLinux(outDir, 0); // Creating dirs
    } else {
        dirCreatorLinux(outDir, 0); // Creating dirs
        termuxPermissionNeeded = dirCreatorLinux(outDirTermux, 1); // Creating dirs
        if (termuxPermissionNeeded >= 1) {
            system("termux-setup-storage");
        }
    }

    // Generating PNG images

    srand((unsigned int)time(NULL)); // Seed the random number generator
    int i = 0;
    int errorCount = 0;

    printDebugPlusInt("Terminal height = ", terminalHeight);
    printDebugPlusInt("Terminal width = ", terminalWidth);


    // Multithread stuff
    pthread_mutex_init(&mutex, NULL); // init the mutex.
    pthread_t progressThread;
    struct ProgressBarArgs* args = (struct ProgressBarArgs*)malloc(sizeof(struct ProgressBarArgs));
    pthread_create(&progressThread, NULL, multiThreadedProgressbar, (void*)args);

    // Start of the image loop
    for (i = 1; i <= count; i++) {
        char imagename[30];

        // printDebugPlusInt("gentime", genTime);
        getTerminalSize(&terminalHeight, &terminalWidth);

        if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
            perror("clock_gettime");
            return 1;
        }

        // Do the progressbar


        double genTime = (double)ts.tv_sec + (double)ts.tv_nsec / 1.0e9;


        // New stuff -----------------------------------------------------------------------------



        args->progress = i;
        args->total = count;
        args->length = terminalWidth - 35;
        args->time = genTime;







        //progressbar(i, count, terminalWidth - 30, genTime); -----------------------------

        // Create file for image
        sprintf(imagename, "%s/random_image%d.png", outDir, i);

        // Generate images and count the errors.
        errorCount = errorCount + generateImage(imagename, width, height, alpha, allowDebugInfo);
    }

    pthread_join(progressThread, NULL);
    pthread_mutex_destroy(&mutex);
    free(args);

    printf("\n");

    if (termuxExternal) {
        int shellCommandLenght = strlen("mv ") + strlen(outDir) + strlen(" ") + strlen(outDirTermux) + 1;
        char shellCommand[shellCommandLenght];

        shellCommand[0] = '\0'; // Initialize it as an empty string

        strcat(shellCommand, "rm -rf ");
        strcat(shellCommand, outDirTermux);
        strcat(shellCommand, "out");
        printDebugPlusStr("Shell command: ", shellCommand);

        system(shellCommand); // Removing dirs to avoid write error

        shellCommand[0] = '\0'; // Initialize it as an empty string

        strcat(shellCommand, "mv ");
        strcat(shellCommand, outDir);
        strcat(shellCommand, " ");
        strcat(shellCommand, outDirTermux);
        printDebugPlusStr("Shell command: %s\n", shellCommand);

        system(shellCommand); // Moving dirs to external
    }

    // Get the current time in UTC
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        perror("clock_gettime");
        return 1;
    }

    double endTime = (double)ts.tv_sec + (double)ts.tv_nsec / 1.0e9;

    double fullTime = endTime - startTime;

    // Error number counting
    if (errorCount == 0) {
        if (count > 1) {
            printf("%d random images generated successfully in %lf seconds.\n", i - 1, fullTime);
        } else if (count == 1) {
            printf("1 random image generated successfully in %lf seconds.\n", fullTime);
        } else if (count == 0) {
            printf("0 random image generated in %lf seconds.\n", fullTime);
        }

    } else {
        printf("%d random image(s) generated with %d error(s) in %lf seconds.\n", i, errorCount, fullTime);
        return 1;
    }

    errorFileCloser();

    return 0;
}
