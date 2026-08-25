#include <string.h>
#include <stdio.h>

const char* GetFileName(void)
{

    const char* last_slash = strrchr(__FILE__, '\\');
    if (last_slash)
        return last_slash + 1;
    return __FILE__;
}
