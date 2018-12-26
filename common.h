#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif /* DEBUG */

#endif /* COMMON_H */
