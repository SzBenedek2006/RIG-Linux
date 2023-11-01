#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>


int dirCreatorLinux (char dirName[]) {       // Starting of the function

    mkdir(dirName, 0700);

    DIR* dir = opendir(dirName);    // dir = dirName.

    if (dir) {                      // If dir exists

        closedir(dir);                  // Close dir!
        return 0;                       // Return directory exists.
    }
    if (ENOENT == errno) {          // If dir not exists
        return 1;                       // Return directory does not exist.
    }
    else {                          // If other fail
        return 2;                       // Return opendir() failed for some other reason.
    }

}
