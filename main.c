#include "PNG_generator.h"
#include "dir_creator.h"
#include "JPEG_generator.h"
#include "my_utils.h"
#include "progressbar.h"
#include "version.h"
#include "args.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>


const int MS = 1000;
char format[4];



int main(int argc, char* argv[]) {

    // Get the current time in UTC
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        perror("clock_gettime");
        return 1;
    }

    *pStartTime = (double)ts.tv_sec + (double)ts.tv_nsec / 1.0e9;



    printf("Welcome to RIG %s!\n", RIG_VERSION);

    // Declaring vars
    unsigned int width = 0;
    unsigned int height = 0;
    bool alpha = false;
    unsigned int count;

    bool help = false;
    bool termuxExternal = false;
    bool random_multiplier = false;
    char outDir[] = "out";
    char androidInternalPath[] = "/storage/emulated/0/";
    uint8_t quality = 100;
    uint8_t r = 255;
    uint8_t g = 255;
    uint8_t b = 255;



    getTerminalSize(&terminalHeight, &terminalWidth);

    /*for (int i = 0; i < terminalHeight - 3; i++) {
     *   printf("\n");
    }*/



    struct Counts counts = {0};
    // Handle the arguments.
    {
        int ret = args(
            argc,
            argv,
            &counts,
            &width,
            &height,
            &alpha,
            &count,
            &help,
            &termuxExternal,
            &random_multiplier,
            &quality,
            &r,
            &g,
            &b,
            format
        );
        if (ret != 0) {
            return ret;
        }
    }


    // Additional checks
    if ((!counts.fCount) && (!counts.hCount) && argc > 1 ) {
        printDebugPlusInt("counts.fCount: %d", counts.fCount);
        printDebugPlusInt("counts.hCount: %d", counts.hCount);
        printf("Format is not set, defaulting to png.\n");
        strcpy(format, "png");

    } else if (counts.aCount && (strcmp(format, "jpg") == 0) ) {
        printf("--alpha (transparency) option will be ignored when using jpeg.\n");

    } else if ((!counts.qCount) && (strcmp(format, "jpg") == 0)) {
        printf("Quality is not set, defaulting to 100.\n");
    }







    // Depends on allowDebugInfo == true
    errorFileOpener();

    printDebugPlusInt("r", r);
    printDebugPlusInt("g", g);
    printDebugPlusInt("b", b);

    // All printDebug depends on errorFileOpener
    printDebugPlusInt("counts.sCount = ", counts.sCount);
    printDebugPlusInt("counts.aCount = ", counts.aCount);
    printDebugPlusInt("counts.cCount = ", counts.cCount);
    printDebugPlusInt("counts.hCount = ", counts.hCount);
    printDebugPlusInt("counts.tCount = ", counts.tCount);
    printDebugPlusInt("counts.dCount = ", counts.dCount);
    printDebugPlusInt("counts.fCount = ", counts.fCount);

    if (argc == 1) {
        printf("Use -h to display help message.\n");
        return 0;
    }

    // Too few arguments warning
    if ((width == 0 || height == 0 || count == 0) && !help) {
        printf("Too few arguments. Width, height or count is 0. Unexpected "
               "behaviour may occur! (Argc = %d)\n", argc);
        return 1;
    }

    // Too many arguments
    if (counts.sCount > 1 || counts.cCount > 1 || counts.aCount > 1 || counts.hCount > 1 || counts.tCount > 1) {
        printf("Too many arguments in the same type.");
        return 1;
    }

    // Helpmsg
    if (help == true) {
        printHelp();
        return 0;
    }

    dirCreatorLinux(outDir, termuxExternal);


    // Generating images

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

    double genTime = 0;
    double genTime1 = 0;
    double genTime2 = (double)ts.tv_sec + (double)ts.tv_nsec / 1.0e9;


    char fileExtension[5];




    // Start of the image loop
    for (i = 1; i <= count; i++) {
        char imagename[30];

        printDebugPlusFloat("gentime:", genTime);
        getTerminalSize(&terminalHeight, &terminalWidth);

        if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
            perror("clock_gettime");
            return 1;
        }


        args->progress = i;
        args->total = count;
        args->length = terminalWidth - 40;
        args->time = genTime * (args->total - args->progress); // To modify

        printDebugPlusFloat("time:", genTime * (args->total - args->progress));



        // Create file for image
        sprintf(imagename, "%s/random_image%d.%s", outDir, i, format);
        printDebugPlusStr("Image name:", imagename);

        if (strcmp(format, "png") == 0) {
            // Write PNG file
            errorCount = errorCount + generatePNG(imagename, width, height, alpha, allowDebugInfo, r, g, b, random_multiplier);
        } else {
            // Write JPEG file
            generateJPEG(imagename, width, height, quality, r, g, b, random_multiplier);
        }





        if (i == 1) {
            printDebug("First iteration of image gen loop.");
        }




        // Time for the progressbar
        genTime1 = genTime2;
        genTime2 = (double)ts.tv_sec + (double)ts.tv_nsec / 1.0e9;
        genTime = genTime2 - genTime1;


        printDebugPlusFloat("genTime1:", genTime1);
        printDebugPlusFloat("genTime2:", genTime2);

    }





    pthread_join(progressThread, NULL);
    pthread_mutex_destroy(&mutex);
    free(args);

    printf("\n");

    if (termuxExternal) {
        printf("Moving images to internal storage...\n");
        int shellCommandLenght = strlen("mv ") + strlen(outDir) + strlen(" ") + strlen(androidInternalPath) + 1;
        char shellCommand[shellCommandLenght];

        printf("    Removing previously generated folder\n");
        shellCommand[0] = '\0'; // Initialize it as an empty string

        strcat(shellCommand, "rm -rf ");
        strcat(shellCommand, androidInternalPath);
        strcat(shellCommand, outDir);
        printDebugPlusStr("Shell command:", shellCommand);

        system(shellCommand); // Removing dirs to avoid write error

        printf("    Moving files\n");
        // TODO: Make a progressbar
        // use ls and mv -v (verbose flag) to check the strings
        // The directory will be made with dirCreatorLinux, so the files should be only moved to it.
        shellCommand[0] = '\0'; // Initialize it as an empty string

        strcat(shellCommand, "mv ");
        strcat(shellCommand, outDir);
        strcat(shellCommand, " ");
        strcat(shellCommand, androidInternalPath);
        printDebugPlusStr("Shell command:", shellCommand);

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
