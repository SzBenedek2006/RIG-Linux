#include "PNG_generator.c"
#include "dir_creator.c"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>


int main(int argc, char *argv[]) {

  printf("Welcome to RIG\n\n");

  // Declaring vars
  unsigned int width;
  unsigned int height;
  bool alpha = false;
  unsigned int count;
  int n;
  bool help = false;
  bool termuxExternal = false;
  char outDir[] = "out";
  char outDirTermux[] = "/storage/emulated/0/";
  int termuxPermissionNeeded = 0;
  bool allowDebugInfo = false;
  int threadNumber = 1;


  // Number of the same arguments
  int sCount = 0;   // -s, --size
  int cCount = 0;   // -c --count
  int aCount = 0;   // -a --alpha
  int hCount = 0;   // -h --help
  int tCount = 0;   // --termux-external
  int dCount = 0;   // -d --debug
  int trCount = 0;  // -t --thread-count





  // Handle the arguments.
  for (n = 1; n < argc; n++) {
    if (strcmp(argv[n], "-s") == 0 || strcmp(argv[n], "--size") == 0) { // -s,
      sCount++;
      if (argv[n + 1] >= 0) {
        height = atoi(argv[n + 1]);
      }
      if (argv[n + 2] >= 0) {
        width = atoi(argv[n + 2]);
      }
    } else if (strcmp(argv[n], "-a") == 0 ||
               strcmp(argv[n], "--alpha") == 0) { // If n-th arg        -a,
      alpha = true;
      aCount++;
    } else if (strcmp(argv[n], "-c") == 0 || strcmp(argv[n], "--count") == 0) { // If n-th arg      -c,
      count = atoi(argv[n + 1]);
      cCount++;
    } else if (strcmp(argv[n], "-h") == 0 ||
               strcmp(argv[n], "--help") == 0) { // If n-th arg       -h,
      help = true;
      hCount++;
    } else if (strcmp(argv[n], "--termux-external") == 0) { // If n-th arg -a,
      termuxExternal = true;                                // to implement
      tCount++;                                             // to implement
    } else if (strcmp(argv[n], "-d") == 0 || strcmp(argv[n], "--debug") == 0) { // If n-th arg -a,
      allowDebugInfo = true;                      // to implement
      dCount++;                                   // to implement
    } else if (strcmp(argv[n], "-t") == 0 || strcmp(argv[n], "--thread-count") == 0) { // If n-th arg      -c,
      threadNumber = atoi(argv[n + 1]);
      trCount++;
    }
  }

  // Print the argument counts
  if (allowDebugInfo) {
    printf("sCount = %d\naCount = %d\ncCount = %d\nhCount = %d\ntCount = %d\ndCount = %d\n", sCount, aCount, cCount, hCount, tCount, dCount);

  }


  // Print the arguments
  if (allowDebugInfo) {
    for (int i = 0; i <= argc; i++) {
      printf("Argv%d = %s\n", i, argv[i]);
    }
  }

  // Too few arguments warning
  if ((width == 0 || height == 0 || count == 0) && !help) {
    printf("Too few arguments or width, height or count is 0. Unexpected "
           "behaviour may occur! (Argc = %d)\n Use -h to print help message.\n",
           argc);
  }

  // Too many arguments
  if (sCount > 1 || cCount > 1 || aCount > 1 || hCount > 1 || tCount > 1) {
    printf("Too many arguments in the same type.");
    return 1;
  }

  // Helpmsg
  if (help == true) {
    printf("Hi, options are the following:\n    '-s' or '--size' <height "
           "width>\n    "
           "'-a' or '--alpha' (this toggles transparency in image formats that "
           "support it)\n    '-c' or '--count' <number>\n    "
           "'--termux-external' (uses your internal storage on android)\n    "
           "'-d' or '--debug' (print debug info)\n    '-t' or '--thread-count' <the number of threads> (it defaults to 1)\n    '-h' or '--help' (this "
           "message)\n\n    Example: -s 10 20 -a -c 10\n");
    return 0;
  }

  if (!termuxExternal) {
    dirCreatorLinux(outDir, 0); // Creating dirs
  } else {
    dirCreatorLinux(outDir, 0);                                // Creating dirs
    termuxPermissionNeeded = dirCreatorLinux(outDirTermux, 1); // Creating dirs
    if (termuxPermissionNeeded >= 1) {
      system("termux-setup-storage");
    }
  }



  struct PNGArguments {
    char imagename[30];
    int width;
    int height;
    bool alpha;
    bool allowDebugInfo;
  } pngArguments;

  pngArguments.width = width;
  pngArguments.height = height;
  pngArguments.alpha = alpha;
  pngArguments.allowDebugInfo = allowDebugInfo;


srand((unsigned int)time(NULL)); // Seed the random number generator
  int i = 0;
  int errorCount = 0;



  if (allowDebugInfo) {
    printf("(count / threadNumber) = %d\n", (count / threadNumber));
    printf("Now generating using the threaded (first) for loop:\n");
}


int outerLoopCount = 0;
int innerLoopCount = 0;
int imageCounter = 0;






  // Generating PNG images
  for (i = 1; i <= (count / threadNumber); i++) { // it is an int devision so dont forget to create the remaining images afterwards

    pthread_t thread_ids[threadNumber]; // creating thread ids for the threads // kipróbálni +1-et levenni

    int threadNumberCounter = 0;
    for (int x = 0; x < threadNumber; x++){
      imageCounter++;

      sprintf(pngArguments.imagename, "%s/random_image%d.png", outDir, (imageCounter));
      pthread_create(&thread_ids[x], NULL, generateImage, &pngArguments);
      sleep(0);

      if (allowDebugInfo) {
        printf("i = %d\n", i);
      }

      innerLoopCount++;
      threadNumberCounter++;
    }

    for (int z = 0; z < threadNumber; z++){
      if (allowDebugInfo){
        printf("Waiting for thread %d...\n", z);
      }
      pthread_join(thread_ids[z], NULL);
    }

    outerLoopCount++;
  }


  if (allowDebugInfo) {
    printf("i after threaded for loop = %d\n", i);
    printf("Now generating using the single thread (second) for loop:\n");
  }

  // (count % threadNumber) create the remaining images afterwards (for loop)

  for (int j = 0; j <= (count % threadNumber); j++) {
    sprintf(pngArguments.imagename, "%s/random_image%d.png", outDir, imageCounter);
    pthread_t thread_id1; // variable for generateimage thread id
    pthread_create(&thread_id1, NULL, generateImage, &pngArguments);
    pthread_join(thread_id1, NULL);
    imageCounter++;
  }







  if (termuxExternal) {
    int shellCommandLenght =
        strlen("mv ") + strlen(outDir) + strlen(" ") + strlen(outDirTermux) + 1;
    char shellCommand[shellCommandLenght];

    shellCommand[0] = '\0'; // Initialize it as an empty string

    strcat(shellCommand, "rm -rf ");
    strcat(shellCommand, outDirTermux);
    strcat(shellCommand, "out");

    if (allowDebugInfo) {printf("Shell command: %s\n", shellCommand);}
    system(shellCommand); // Removing dirs to avoid write error

    shellCommand[0] = '\0'; // Initialize it as an empty string

    strcat(shellCommand, "mv ");
    strcat(shellCommand, outDir);
    strcat(shellCommand, " ");
    strcat(shellCommand, outDirTermux);

    if (allowDebugInfo) {
      printf("Shell command: %s\n", shellCommand);
    }
    system(shellCommand); // Moving dirs to external
  }








  // Error number counting
  if (errorCount == 0) {
    if (count > 1) {
      printf("%d random images generated successfully.\n", i - 1);
    } else if (count == 1) {
      printf("1 random image generated successfully.\n");
    } else if (count == 0) {
      printf("0 random image generated.\n");
    }

  } else {
    printf("%d random image(s) generated with %d error(s).\n", i, errorCount);
    return 1;
  }

  if (allowDebugInfo) {
    printf("Outer loop: %d\nInner loop: %d\n", outerLoopCount, innerLoopCount);
}



  return 0;
}
