#include <stdio.h>

#define DESIGN_PATTERN 0

void callback(void) { }

// original function pointer function
void functionPtr(void (*callback_ptr)())
{
    (*callback_ptr) (); // callback function
}

void functionPtr_test(void (*callback_ptr)())
{
    #if DESIGN_PATTERN
        //functionPtr_dp(callback_ptr);
    #else
        functionPtr(callback_ptr);
    #endif
}
//Callback added in main()
int main(int argc, char *argv[])
{
    void (*callback_ptr)(void) = &callback;
    functionPtr_test(callback_ptr);

    return 0;
}