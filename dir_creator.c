#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

int dirCreatorLinux(char dirName[], int isTermux) { // Starting of the function


  mkdir(dirName, 0700);

  if (isTermux == 0) {



    DIR *dir = opendir(dirName); // dir = dirName.

    if (dir) { // If dir exists

      closedir(dir);              // Close dir!
      return 0;                   // Return directory exists.
    } else if (ENOENT == errno) { // If dir not exists
      return 1;                   // Return directory does not exist.
    } else {                      // If other fail
      return 2; // Return opendir() failed for some other reason.
    }
  } else {
    DIR *dir = opendir(dirName); // dir = dirName.

    if (dir) { // If dir exists

      closedir(dir);              // Close dir!
      return 0;                   // Return directory exists.
    } else if (ENOENT == errno) { // If dir not exists
      return 1;                   // Return directory does not exist.
    } else {                      // If other fail
      return 2; // Return opendir() failed for some other reason.
    }
  }
}

// Megcsinálni a termux-setup-storage-t
