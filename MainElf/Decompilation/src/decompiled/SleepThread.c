#include <stdio.h>
#include <unistd.h>

void SleepThread()
{
    printf("Sleeping main thread\n");
    sleep(0xffffffffu); // This is so janky   
    // but it equates to about 50000 days of time
    // So its probably fine 
}