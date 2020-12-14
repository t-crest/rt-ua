#include <stdio.h>

#ifndef APPLY_TRANSFORMATION_RULE
// original for loop function
int for_loop(int c)
{
    int i, n = 0;

    for(i=0;i<c;i++)
    {
        n++;
        //if(n==2) i++;
    }
    return n;
}
#else
// for loop with design pattern applied
int for_loop(int c)
{
    int i, n = 0;

    if(c > 10) return -1;   // check if c ist bigger then max loopbound

    _Pragma("loopbound min 1 max 10")  // maximum 10 for loop iterations
    for(i=0;i<c;i++)
    {
        n++;
    }
    return n;
}
#endif

void for_loop_test()
{
    int c = 10;
    int ret = -1;

    ret = for_loop(c);
}

int main(int argc, char *argv[])
{
    for_loop_test();

    return 0;
}
