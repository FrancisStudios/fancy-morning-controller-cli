#include "headless.h"

namespace FancyHeadless
{
    void dispatch(char *arg)
    {
        printf("headless mode \n");
        printf("arg: %s", arg);

        if (strcmp(arg, "hello\n"))
            printf("yes, hello \n");
    }
}