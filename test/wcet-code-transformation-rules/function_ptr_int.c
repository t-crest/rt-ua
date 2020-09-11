int callback1(void) __attribute__((noinline));
int callback2(void) __attribute__((noinline));
int functionPtrInt_test(int (*callback_ptr)()) __attribute__((noinline));

int callback1(void) { return 3; }
int callback2(void) { return 4; }

int functionPtrInt_test(int (*callback_ptr)())
{
    return (*callback_ptr) (); // callback function
}

//Callback added in main()
int main(int argc, char *argv[])
{
    if(argc%2 == 0)
        functionPtrInt_test(&callback1);
    else
        functionPtrInt_test(&callback2);

    return 0;
}
