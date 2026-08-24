#pragma once

#include <stdio.h>

#ifdef MYNDEBUG

#define MyAssert(val, pf)

#else

#define MyAssert(val, pf)     \
    if (!val) \
    {      \
        pf(); \
        printf("%s:%d: In function '%s'\n", GetFileName(), __LINE__, __func__); \
        printf("%s:%d: error on line %d", GetFileName(), __LINE__, __LINE__); \
        abort(); \
      \
    }

#endif


const char*  GetFileName              (void);


const char* GetFileName(void)
{

    const char* last_slash = strrchr(__FILE__, '\\');
    if (last_slash)
        return last_slash + 1;
    return __FILE__;
}
