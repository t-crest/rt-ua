#include <stdio.h>

void myFunction(void) { return; }
void (*callback_ptr)();

void registerCallback(void (*c)()) {
    callback_ptr = c;
}

void callCallback() {
    callback_ptr();
    return;
}

void functionPtrVoid_test()
{
    registerCallback(&myFunction);
    callCallback();
}

//Callback added in main()
int main(int argc, char *argv[])
{
    functionPtrVoid_test();

    return 0;
}
