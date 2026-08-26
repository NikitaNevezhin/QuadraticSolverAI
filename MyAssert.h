#ifndef MyAssert_h

#define MyAssert_h

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef MYNDEBUG

#define MyAssert(val, pf)

#else

#define MyAssert(val, pf) \
    if (!val) \
    {      \
        \
        const char* file_name = strrchr(__FILE__, '\\'); \
        if (!file_name)                        \
            file_name = __FILE__; \
        else   \
            file_name++; \
     \
        pf(); \
        printf("%s:%d: In function '%s'\n", file_name, __LINE__, __func__); \
        printf("%s:%d: error on line %d", file_name, __LINE__, __LINE__); \
        abort(); \
    \
    }

#endif


#endif
