#include <stdio.h>
#include <stdint.h>
#include <time.h>

void timespec_diff(struct timespec *start, struct timespec *stop,
                   struct timespec *result)
{
    if ((stop->tv_nsec - start->tv_nsec) < 0) {
        result->tv_sec = stop->tv_sec - start->tv_sec - 1;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
    } else {
        result->tv_sec = stop->tv_sec - start->tv_sec;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec;
    }

    return;
}

uint32_t iter(uint32_t b, uint32_t e)
{
    uint32_t pow=1;
    for(uint32_t i=0;i<e;i++)
        pow=pow*b;
    return pow;
}

uint32_t rec(uint32_t b, uint32_t e)
{
    if(e==0)
        return 1;
    else
        return b*rec(b,e-1);
}

uint32_t (*pw[])(uint32_t b, uint32_t e) = {iter, rec};

uint32_t calc_pow(uint32_t b, uint32_t e, uint32_t t, struct timespec *diff)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    uint32_t ret = pw[t](b, e);
    clock_gettime(CLOCK_MONOTONIC, &end);
    timespec_diff(&start,&end,diff);

    return ret;
}

int main(void)
{
    struct timespec diff;
    uint32_t t=0;
    uint32_t ret=calc_pow(2, 3, t, &diff);
    printf("%ld\n", (long)diff.tv_nsec);
    printf("%lu\n", ret);
    return 0;
}