#include <stdio.h>

void callback(void) { return; }

void functionPtrVoid_test(void (*callback_ptr)())
{
    return (*callback_ptr) (); // callback function
}

//Callback added in main()
int main(int argc, char *argv[])
{
    functionPtrVoid_test(&callback);

    return 0;
}
