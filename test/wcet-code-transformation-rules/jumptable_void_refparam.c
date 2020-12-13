// This example works for both cases, DESIGN_PATTERN = 0 and DESIGN_PATTERN = 1
// But it should not work for DESIGN_PATTERN = 0
#include <stdio.h>

#define DESIGN_PATTERN 1

int my_global_var = 0;

void func0 (int *res) { *res += my_global_var; }
void func1 (int *res) { *res += my_global_var; }

void (*pf[])(int *res) = {func0, func1};

#if DESIGN_PATTERN == 0
void jumpTableRefparam(int t, int *res) // original jumptable function
{
    pf[t](res);
}
#else
void jumpTableRefparam(int t, int *res) // jump table with design pattern applied
{
    switch (t) {
        case 0:
            func0(res);
            break;
        case 1:
            func1(res);
            break;
        default:
            break;
    }
}
#endif


void jumpTableRefparam_test(int t, int *res)
{
    jumpTableRefparam(t, res);
}

int main(int argc, char *argv[])
{
    int res = 0;
    jumpTableRefparam_test(argc%2, &res);
    printf("res: %d", res);

    return 0;
}
