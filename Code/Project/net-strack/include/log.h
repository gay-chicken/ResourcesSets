#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>

#define LOG_ERROR(Fn, Err)                                                                 \
    do                                                                                     \
    {                                                                                      \
        fprintf(stderr, "%d:%s - Error in %s: %s\n", __LINE__, __FUNCTION__, (Fn), (Err)); \
        exit(1);                                                                           \
    } while (0)

#endif