#include <stdio.h>

int callback(void) { return 3; }

int functionPtrInt_test(int (*callback_ptr)())
{
    return (*callback_ptr) (); // callback function
}

//Callback added in main()
int main(int argc, char *argv[])
{
    functionPtrInt_test(&callback);

    return 0;
}
