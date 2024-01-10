// Multithreaded Image Generator
#include "PNG_generator.c"
#include <pthread.h>



int mig (int width, int height, bool alpha, int count, int threadNumber, char *outDir, bool allowDebugInfo) {

  struct PNGArguments {
    char imagename[30];
    int width;
    int height;
    bool alpha;
    bool allowDebugInfo;
    int count;
  } pngArguments;

  pngArguments.width = width;
  pngArguments.height = height;
  pngArguments.alpha = alpha;
  pngArguments.allowDebugInfo = allowDebugInfo;
  pngArguments.count = count;

    srand((unsigned int)time(NULL)); // Seed the random number generator
    int i = 0;


    int outerLoopCount = 0;
    int innerLoopCount = 0;
    int imageCounter = 0;

  // Generating PNG images
  for (i = 1; i <= (count / threadNumber);
       i++) { // it is an int devision so dont forget to create the remaining
              // images afterwards

    pthread_t thread_ids[threadNumber]; // creating thread ids for the threads
                                        // // kipróbálni +1-et levenni

    int runningThreads = 0;                  // counter for pthreads
    for (int x = 0; x < threadNumber; x++) { // - runningThreads = fasság
      imageCounter++;

      sprintf(pngArguments.imagename, "%s/random_image%d.png", outDir,
              (imageCounter));
      pthread_create(&thread_ids[x], NULL, generatePNG, &pngArguments);
      sleep(0);

      if (allowDebugInfo) {
        printf("i = %d\n", i);
      }

      innerLoopCount++; // just for debug
      runningThreads++; // just for debug
      /*
      if (imageCounter == count) {
        break;
      }
      */
    }

    // Joining threads  TODO: make it always use threads instead of launching
    // threadNumber threads and waiting for all to join.
    for (int z = 0; z < threadNumber; z++) {
      if (allowDebugInfo) {
        printf("Waiting for thread %d...\n", z);
      }
      pthread_join(thread_ids[z], NULL);
    }

    outerLoopCount++; // just for debug

    // if (imageCounter == count) {
    //   break;
    // }
  }

  if (allowDebugInfo) {
    printf("i after threaded for loop = %d\n", i);
    printf("Now generating using the single thread (second) for loop:\n");
  }

  // (count % threadNumber) create the remaining images afterwards (for loop)

  for (int j = 0; j <= (count % threadNumber); j++) {
    sprintf(pngArguments.imagename, "%s/random_image%d.png", outDir,
            imageCounter);
    pthread_t thread_id1; // variable for generatePNG thread id
    pthread_create(&thread_id1, NULL, generatePNG, &pngArguments);
    pthread_join(thread_id1, NULL);
    imageCounter++;
  }

  if (allowDebugInfo) {
    printf("Outer loop: %d\nInner loop: %d\n", outerLoopCount, innerLoopCount);
  }



  return ((i - 1) * threadNumber);
}
