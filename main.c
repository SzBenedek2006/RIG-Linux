#include "PNG_generator.c"
#include "dir_creator.c"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {

  printf("Welcome to RIG\n\n");

  unsigned int width;
  unsigned int height;
  bool alpha = false;
  unsigned int count;
  int n;
  bool help = false;

  for (n = 1; n < argc; n++) {
    if (strcmp(argv[n], "-s") == 0 || strcmp(argv[n], "--size") == 0) { // Ha n-edik arg -s,
      height = atoi(argv[n + 1]);
      width = atoi(argv[n + 2]); // Width = n+2-edik arg
    }
    else if (strcmp(argv[n], "-a") == 0 || strcmp(argv[n], "--alpha") == 0) {
      alpha = true;
    } else if (strcmp(argv[n], "-c") == 0 || strcmp(argv[n], "--count") == 0) {
      count = atoi(argv[n + 1]);
    } else if (strcmp(argv[n], "-h") == 0 || strcmp(argv[n], "--help") == 0) {
      help = true;
    }
  }



  // Helpmsg
  if (help == true) {
    printf("Hi, options are the following:\n '-s' or '--size' <height width>\n '-a' or '--alpha' (this toggles transparency)\n '-c' or 'count' <number>\n 'h' or '--help' (this message)\n\n Example: ./main -s 10 20 -a -c 10");
    return 0;
  }

  // Too few arguments warning
  if (width == 0 || height == 0 || count == 0) {
    printf("Too few arguments, unexpected behaviour may occur! (Argc = %d)\n", argc);
  }

  srand((unsigned int)time(NULL)); // Seed the random number generator
  int i;
  int errorCount = 0;

  for (i = 1; i <= count; i++) {
    char imagename[30];

    dirCreatorLinux("out");

    sprintf(imagename, "out/random_image%d.pgm", i);
    errorCount = errorCount + generateImage(imagename, width, height, alpha);
  }

  if (errorCount == 0) {
    if (count > 1) {
      printf("%d random image(s) generated successfully.\n", i - 1);
    } else if (count == 1) {
      printf("1 random image generated successfully.\n");
    } else if (count == 0) {
      printf("0 random image generated.\n");
    } else {
      printf("An error occured, probably related to overflow.\n");
    }

  }



  else {
    printf("Random image(s) generated with %d error(s).\n", errorCount);
  }

  return 0;
}
