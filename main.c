#include "PNG_generator.c"
#include "dir_creator.c"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {

  printf("Welcome to RIG\n\n");

  // Declaring vars
  unsigned int width;
  unsigned int height;
  bool alpha = false;
  unsigned int count;
  int n;
  bool help = false;
  bool termuxExternal;
  char outDir[] = "out";
  char outDirTermux[] = "/storage/emulated/0/";
  int termuxPermissionNeeded = 0;
  bool allowDebugInfo = false;

  // Number of the same arguments
  int sCount = 0; // -s, --size
  int cCount = 0; // -c --count
  int aCount = 0; // -a --alpha
  int hCount = 0; // -h --help
  int tCount = 0; // --termux_external
  int dCount = 0; // -d --debug

  // Print the arguments
  /*for (int i = 0; i <= argc; i++) {
    printf("Argv%d = %s\n", i, argv[i]);
  }
  */

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
    } else if (strcmp(argv[n], "-c") == 0 ||
               strcmp(argv[n], "--count") == 0) { // If n-th arg      -c,
      count = atoi(argv[n + 1]);
      cCount++;
    } else if (strcmp(argv[n], "-h") == 0 ||
               strcmp(argv[n], "--help") == 0) { // If n-th arg       -h,
      help = true;
      hCount++;
    } else if (strcmp(argv[n], "--termux-external") == 0) { // If n-th arg -a,
      termuxExternal = true;                                // to implement
      tCount++;                                             // to implement
    } else if (strcmp(argv[n], "-d") == 0 ||
               strcmp(argv[n], "--debug") == 0) { // If n-th arg -a,
      allowDebugInfo = true;                      // to implement
      dCount++;                                   // to implement
    }
  }

  // Print the arguments
  // printf("%d\n%d\n%d\n%d\n", sCount, aCount, cCount, hCount);

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
           "'-d' or '--debug' (print debug info)\n    '-h' or '--help' (this "
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

  srand((unsigned int)time(NULL)); // Seed the random number generator
  int i = 0;
  int errorCount = 0;

  // Generating PNG images
  for (i = 1; i <= count; i++) {
    char imagename[30];

    // Generate images and count the errors.
    sprintf(imagename, "%s/random_image%d.png", outDir, i);
    errorCount = errorCount +
                 generateImage(imagename, width, height, alpha, allowDebugInfo);
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

    if (allowDebugInfo) {printf("Shell command: %s\n", shellCommand);}
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

  return 0;
}
