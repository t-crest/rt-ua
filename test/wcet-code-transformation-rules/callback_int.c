#include <stdio.h>

int myFunction1(void) { return 5; }
int myFunction2(void) { int x = 5; x *= x; return x; }
int (*callback_ptr)();

void registerCallback(int (*c)()) {
    callback_ptr = c;
}

int callCallback() {
    return callback_ptr();
}

void callbackInt_test()
{
    callCallback();
}

//Callback added in main()
int main(int argc, char *argv[])
{
//    if (argc == 1)
//        registerCallback(&myFunction1);
//    else if (argc == 2)
        registerCallback(&myFunction2);
    callbackInt_test();

    return 0;
}
