#include <stdio.h>
#include <stdint.h>
#include <machine/rtc.h>

#define EMAX 32
#define NMAX 10

uint32_t top=-1,stack[EMAX];
void push(uint32_t v);
uint32_t pop();

void push(uint32_t v)
{
	if(top==EMAX-1)
	{
		//printf("Stack is full!\n");
	}
	else
	{
		top=top+1;
		stack[top]=v;
	}
}
 
uint32_t pop()
{
	if(top==-1)
	{
		//printf("Stack is empty!\n");
        return -1;
	}
	else
	{
        return stack[top--];
	}
}

void visualizeEvenValue(long v) {
    // printf("Even: %ld\n", v);
    // Do something with v
    ;
}

void visualizeOddValue(long v) {
    // printf("Odd: %ld\n", v);
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
    uint32_t ret=1;

    if(e > EMAX) return 0;

    _Pragma("loopbound min 0 max EMAX")
    for(uint32_t i=e; i>0; i--)
        push(b);

    _Pragma("loopbound min 0 max EMAX")
    for(uint32_t i=e; i>0; i--)
        ret=ret*pop();

    return ret;
}

void (*visualize[])(long) = {visualizeEvenValue, visualizeOddValue};

void measure_time(uint32_t b, uint32_t e, uint8_t n, uint64_t *diff)
{
    uint64_t start, end;
    uint32_t result;

    if(n > NMAX) return;

    start=get_cpu_usecs();
    _Pragma("loopbound min 0 max NMAX")
    for(int i = 0; i < n; i++) {
        result = power(b, e);
    }
    end=get_cpu_usecs();
    *diff = end - start;

    switch(result%2) {
        case 0: visualizeEvenValue(result); break;
        case 1: visualizeOddValue(result); break;
    }
}

int main(void)
{
    uint64_t diff;
    measure_time(3, 2, 10, &diff);
    printf("time: %lld usec\n", diff);
    return 0;
}
