#include "ccache.h"

int usleep(useconds_t time)
{
    time /= 1000;
    Sleep(time);
    return 0;
}