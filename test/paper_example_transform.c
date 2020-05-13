#include <stdio.h>
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

int iter(int b, int e)
{
    int pow=1;
    for(int i=0;i<e;i++)
        pow=pow*b;
    return pow;
}

int rec(int b, int e)
{
    if(e==0)
        return 1;
    else
        return b*rec(b,e-1);
}

int (*pw[])(int b, int e) = {iter, rec};

int calc_pow(int b, int e, int t, struct timespec *diff)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    int ret = pw[t](b, e);
    clock_gettime(CLOCK_MONOTONIC, &end);
    timespec_diff(&start,&end,diff);

    return ret;
}

int main(void)
{
    int t=0;
    struct timespec diff;
    int ret=calc_pow(2, 3, t, diff);
    printf("%ld\n", (long)diff.tv_nsec);
    printf("%i\n", ret);
    return 0;
}

/* TODO
    recursive auf stack
    clock_gettime auf get_cpu_usecs 
    wcet berechnen
*/