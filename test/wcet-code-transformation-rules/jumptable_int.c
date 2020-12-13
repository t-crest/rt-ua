// This example works for both cases, DESIGN_PATTERN = 0 and DESIGN_PATTERN = 1
// But it should not work for DESIGN_PATTERN = 0
#include <stdio.h>

#define DESIGN_PATTERN 0
int my_global_var = 0;

int func0 (void) { return my_global_var + 1;}
int func1 (void) { return my_global_var + 2;}

int (*pf[])(void) = {func0, func1};

#if DESIGN_PATTERN == 0
int jumpTableInt(int t) // original jumptable function
{
    return pf[t]();
}
#else
int jumpTableInt(int t) // jump table with design pattern applied
{
    switch (t) {
        case 0:
            return func0();
            break;
        case 1:
            return func1();
            break;
        default:
            break;
    }
    return -1;
}
#endif


int jumpTableInt_test(int t)
{
    return jumpTableInt(t);
}

int main(int argc, char *argv[])
{
    int res = jumpTableInt_test(argc%2);
    printf("res: %d", res);

    return 0;
}
