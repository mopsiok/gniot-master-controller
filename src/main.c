
#include <stdio.h>
#include <unistd.h>

#include "bsp.h"

#define LOOP_COUNT      100
#define LOOP_DELAY_US   100000

int main()
{
    float dt = LOOP_DELAY_US / 1000000.0f;

    int ret = bspInit();
    if (ret < 0)
    {
        return ret;
    }

    for (int i = 0; i <= LOOP_COUNT; i++)
    {
        printf("elapsed: %05.2f\n", dt * i);

        bspBeep();
        usleep(LOOP_DELAY_US);
    }

    printf("Done.\n");
    return 0;
}
