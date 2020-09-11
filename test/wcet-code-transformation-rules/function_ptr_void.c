#include <stdio.h>

void callback1(void) __attribute__((noinline));
void callback2(void) __attribute__((noinline));
void functionPtrInt_test(void (*callback_ptr)()) __attribute__((noinline));

void callback1(void) { ; }
void callback2(void) { ; }

void functionPtrVoid_test(void (*callback_ptr)())
{
    (*callback_ptr) (); // callback function
}

//Callback added in main()
int main(int argc, char *argv[])
{
    if(argc%2 == 0)
        functionPtrVoid_test(&callback1);
    else
        functionPtrVoid_test(&callback2);

    return 0;
}
