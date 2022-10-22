
#include <stdio.h>
#include <unistd.h>

#include "bsp.h"

#define LOOP_COUNT      30
#define LOOP_DELAY_US   100000

int main()
{
    int ret = bspInit();
    if (ret < 0)
    {
        return ret;
    }

    for (int i = 0; i <= LOOP_COUNT; i++)
    {
        bspBeep();
        usleep(LOOP_DELAY_US);
    }

    printf("Done.\n");
    return 0;
}
