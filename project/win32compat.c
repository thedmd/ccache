#include "ccache.h"

void win32usleep(size_t time)
{
    time /= 1000;
    Sleep(time);
}