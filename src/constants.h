#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <limits.h>

#define KEY_LENGTH BUFSIZ

// Some platforms (e.g., POSIX) define PATH_MAX, others (e.g., Windows) do not.
// To maintain portability, PATH_MAX is used when available; 
// otherwise, a fallback to 260 is applied (MAX_PATH on Windows).
#ifdef PATH_MAX
    #define PATH_LENGTH PATH_MAX
#else
    #define PATH_LENGTH 260
#endif

#endif // CONSTANTS_H