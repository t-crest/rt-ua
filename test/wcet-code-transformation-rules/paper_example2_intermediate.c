#include <stdio.h>
#include <stdint.h>
#include <machine/rtc.h>



void visualizeEvenValue(long v) {
    printf("Even: %ld\n", v);
    // Do something with v
    ;
}

void visualizeOddValue(long v) {
    printf("Odd: %ld\n", v);
    // Do something with v
    ;
}

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

uint32_t power(uint32_t b, uint32_t e)
{
    if(e==0)
        return 1;
    else
        return b*power(b,e-1);
}

void (*visualize[])(long) = {visualizeEvenValue, visualizeOddValue};

void measure_time(uint32_t b, uint32_t e, uint8_t n, uint64_t *diff)
{
    uint64_t start, end;
    uint32_t result;

    start=get_cpu_usecs();
    for(int i = 0; i < n; i++) {
        result = power(b, e);
    }
    end=get_cpu_usecs();
    *diff = end - start;

    visualize[result%2](result);
}

int main(void)
{
    uint64_t diff;
    measure_time(3, 2, 100, &diff);
    printf("time: %lld usec\n", diff);
    return 0;
}
