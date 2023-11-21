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



  // Number of the same arguments
  int sCount = 0;
  int cCount = 0;
  int aCount = 0;
  int hCount = 0;


  // Print the arguments
  /*for (int i = 0; i <= argc; i++) {
    printf("Argv%d = %s\n", i, argv[i]);
  }
  */


  for (n = 1; n < argc; n++) {
    if (strcmp(argv[n], "-s") == 0 || strcmp(argv[n], "--size") == 0) { // Ha n-edik arg              -s,
      sCount++; // Adott argument számolása, hogy ne legyen 1-nél több.
      if (argv[n + 1] >= 0) {
        height = atoi(argv[n + 1]);
        };
      if (argv[n + 2] >= 0) {
        width = atoi(argv[n + 2]); // Width = n+2-edik arg
        };
    }
    else if (strcmp(argv[n], "-a") == 0 || strcmp(argv[n], "--alpha") == 0) { // Ha n-edik arg        -a,
      alpha = true;
      aCount++;
    } else if (strcmp(argv[n], "-c") == 0 || strcmp(argv[n], "--count") == 0) { // Ha n-edik arg      -c,
      count = atoi(argv[n + 1]);
      cCount++;
    } else if (strcmp(argv[n], "-h") == 0 || strcmp(argv[n], "--help") == 0) { // Ha n-edik arg       -h,
      help = true;
      hCount++;
    }
  }

  // Print the arguments
  // printf("%d\n%d\n%d\n%d\n", sCount, aCount, cCount, hCount);

  // Too few arguments warning
  if (width == 0 || height == 0 || count == 0) {
    printf("Too few arguments or width, height or count is 0. Unexpected behaviour may occur! (Argc = %d)\n Use -h to print help message.\n", argc);
  }

  // Too many arguments
  if (sCount > 1 || cCount > 1 || aCount > 1 || hCount > 1) {
    printf("Too many arguments in the same type.");
    return 1;
  }



  // Helpmsg
  if (help == true) {
    printf("Hi, options are the following:\n '-s' or '--size' <height width>\n '-a' or '--alpha' (this toggles transparency in image formats that support it)\n '-c' or '--count' <number>\n '-h' or '--help' (this message)\n\n Example: -s 10 20 -a -c 10\n");
  }


  srand((unsigned int)time(NULL)); // Seed the random number generator
  int i;
  int errorCount = 0;

  for (i = 1; i <= count; i++) {
    char imagename[30];

    dirCreatorLinux("out");

    sprintf(imagename, "out/random_image%d.png", i);
    errorCount = errorCount + generateImage(imagename, width, height, alpha);
  }

  if (errorCount == 0) {
    if (count > 1) {
      printf("%d random images generated successfully.\n", i - 1);
    } else if (count == 1) {
      printf("1 random image generated successfully.\n");
    } else if (count == 0) {
      printf("0 random image generated.\n");
    }

  } else {
    printf("Random image(s) generated with %d error(s).\n", errorCount);
    return 1;

  }



  return 0;
}
