#include <stdio.h>

#define DESIGN_PATTERN 0
#define DEBUG 0


// original for loop function
int for_loop(int c)
{
    int i, n = 0;

    for(i=0;i<c;i++)
    {
        n++;
        if(n==2) i++;
    }
    return n;
}

// for loop with design pattern applied
int for_loop_dp(int c)
{
    int i, n = 0;

    if(c > 10) return -1;   // check if c ist bigger then max loopbound

    _Pragma("loopbound min 1 max 10")  // maximum 10 for loop itterations
    for(i=0;i<c;i++)
    {
        n++;
    }
    return n;
}

void for_loop_test()
{
    int c = 10;
    int ret = -1;

    #if DESIGN_PATTERN
        ret = for_loop_dp(c);
    #else
        ret = for_loop(c);
    #endif

    #if DEBUG
    if(ret == -1) printf("loopbound exceeded\n");
    #endif
}

int main(int argc, char *argv[])
{
    for_loop_test();

    return 0;
}