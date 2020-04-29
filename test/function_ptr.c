#include <stdio.h>

#define DESIGN_PATTERN 0

void func0 (void) { }
void func1 (void) { }

// original function pointer function
void functionPtr(int c)
{
    void (*fun_ptr)(void) = &func0;

    if(c==0) fun_ptr = &func0;
    if(c==1) fun_ptr = &func1;

    (*fun_ptr)();
}

// function pointer function with design pattern applied
void functionPtr_dp(int c)
{
    switch (c) {
        case 0:
            func0();
            break;
        case 1:
            func1();
            break;
        default:
            break;
    }
}

void functionPtr_test()
{
    int c=0;

    #if DESIGN_PATTERN
        functionPtr_dp(c);
    #else
        functionPtr(c);
    #endif
}

int main(int argc, char *argv[])
{
    functionPtr_test();

    return 0;
}