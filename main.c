#include "PNG_generator.h"
#include "dir_creator.h"
#include "JPEG_generator.h"
#include "my_utils.h"
#include "progressbar.h"
#include "version.h"

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


int main(int argc, char* argv[])
{

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
    int n;
    bool help = false;
    bool termuxExternal = false;
    bool random_multiplier = false;
    char outDir[] = "out";
    char androidInternalPath[] = "/storage/emulated/0/";
    uint8_t quality = 100;
    uint8_t r = 255;
    uint8_t g = 255;
    uint8_t b = 255;
    int temp = 0;


    getTerminalSize(&terminalHeight, &terminalWidth);

    /*for (int i = 0; i < terminalHeight - 3; i++) {
     *   printf("\n");
    }*/

    // Number of the same arguments
    short unsigned int sCount = 0;      // -s, --size
    short unsigned int cCount = 0;      // -c --count
    short unsigned int aCount = 0;      // -a --alpha
    short unsigned int hCount = 0;      // -h --help
    short unsigned int tCount = 0;      // --termux_external
    short unsigned int dCount = 0;      // -d --debug
    short unsigned int fCount = 0;      // -f --format
    short unsigned int qCount = 0;      // -q --quality
    short unsigned int rgbCount = 0;    // --rgb --RGB
    short unsigned int snCount = 0;     // --sensor-noise



    // Handle the arguments.
    for (n = 1; n < argc; n++) {
        if (strcmp(argv[n], "-s") == 0 || strcmp(argv[n], "--size") == 0) { // -s,
            sCount++;
            if (argv[n + 1] != NULL && argv[n + 1] != NULL) {
                    width = atoi(argv[n + 1]);
                    height = atoi(argv[n + 2]);
                    n += 2;
            } else {
                printf("Size is not specified!\n");
                return 3;
            }
        } else if (strcmp(argv[n], "-a") == 0 || strcmp(argv[n], "--alpha") == 0) { // If n-th arg        -a,
            alpha = true;
            aCount++;
        } else if (strcmp(argv[n], "-c") == 0 || strcmp(argv[n], "--count") == 0) { // If n-th arg      -c,
            if (argv[n + 1] != NULL) {
                count = atoi(argv[n + 1]);
                cCount++;
                n++;
            } else {
                printf("Count is not specified!\n");
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
        } else if (strcmp(argv[n], "-f") == 0 || strcmp(argv[n], "--format") == 0) { // If n-th arg -f
            fCount++;
            if ((argv[n + 1]) != NULL) {
                if (strcmp(argv[n + 1], "png") == 0) {
                    strcpy(format, "png");
                    n++;
                } else if (strcmp(argv[n + 1], "jpeg") == 0 || strcmp(argv[n + 1], "jpg") == 0) {
                    strcpy(format, "jpg");
                    n++;
                 } else {
                    printf("RIG currently only supports png (default) and jpeg as a format option!");
                    return 3;
                 }
            } else {
                printf("--format/-f is not set correctly or left empty, write image format after -f or --format!\n");
                return 3;
            }
        } else if (strcmp(argv[n], "-q") == 0 || strcmp(argv[n], "--quality") == 0) { // If n-th arg -q
            qCount++;
            if ((argv[n + 1]) != NULL) {
                quality = atoi(argv[n + 1]);
                if (quality > 0 && quality <= 100) {
                    n++;
                } else {
                    printf("Quality isn't set correctly!\n");
                    return 3;
                }
            } else {
                printf("Missing quality value after -q or --quality.\n");
                return 3;
            }
        } else if (strcmp(argv[n], "--rgb") == 0 || strcmp(argv[n], "--RGB") == 0) {
            if ((argv[n + 1]) != NULL) {
                temp = atoi(argv[n + 1]);
                if (temp <= 255 && r >= 0) {
                    r = temp;
                } else {
                    printf("Red value is outside of the range (0-255)!\n");
                    return 3;
                }
            } else {
                printf("Red value missing!\n");
                return 3;
            }
            if ((argv[n + 2]) != NULL) {
                temp = atoi(argv[n + 2]);
                if (temp <= 255 && g >= 0) {
                    g = temp;
                } else {
                    printf("Green value is outside of the range (0-255)!\n");
                    return 3;
                }
            } else {
                printf("Green value missing!\n");
                return 3;
            }
            if ((argv[n + 3]) != NULL) {
                temp = atoi(argv[n + 3]);
                printf("atoi %d\n", temp);
                if (temp <= 255 && b >= 0) {
                    b = temp;
                } else {
                    printf("Blue value is outside of the range (0-255)!\n");
                    return 3;
                }
            } else {
                printf("Blue value missing!\n");
                return 3;
            }
            n += 3;
        } else if (strcmp(argv[n], "--sensor-noise") == 0) {
            random_multiplier = true;
        } else { // If there is no known argument at a given argc location.
            printf("Unknown option \"%s\" at the %d. argument. Use -h for help.\n", argv[n], n);
            return 3;
        }
    }

    // Additional checks
    if ((!fCount) && (!hCount) && argc > 1 ) {
        printDebugPlusInt("fCount: %d", fCount);
        printDebugPlusInt("hCount: %d", hCount);
        printf("Format is not set, defaulting to png.\n");
        strcpy(format, "png");

    } else if (aCount && (strcmp(format, "jpg") == 0) ) {
        printf("--alpha (transparency) option will be ignored when using jpeg.\n");

    } else if ((!qCount) && (strcmp(format, "jpg") == 0)) {
        printf("Quality is not set, defaulting to 100.\n");
    }







    // Depends on allowDebugInfo == true
    errorFileOpener();

    printDebugPlusInt("r", r);
    printDebugPlusInt("g", g);
    printDebugPlusInt("b", b);

    // All printDebug depends on errorFileOpener
    printDebugPlusInt("sCount = ", sCount);
    printDebugPlusInt("aCount = ", aCount);
    printDebugPlusInt("cCount = ", cCount);
    printDebugPlusInt("hCount = ", hCount);
    printDebugPlusInt("tCount = ", tCount);
    printDebugPlusInt("dCount = ", dCount);
    printDebugPlusInt("fCount = ", fCount);

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
    if (sCount > 1 || cCount > 1 || aCount > 1 || hCount > 1 || tCount > 1) {
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
        args->length = terminalWidth - 35;
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
