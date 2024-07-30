#ifndef DIR_CREATOR
#define DIR_CREATOR

#include <stdbool.h>
extern int termuxPermissionNeeded;
extern char androidInternalPath[];

int dirCreatorLinux(char dirName[], bool isTermux);

#endif
