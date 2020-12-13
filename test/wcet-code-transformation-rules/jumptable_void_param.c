// This example works for only for DESIGN_PATTNER = 1, as expected
#define DESIGN_PATTERN 1

int my_global_var = 0;

void func0 (int res) { my_global_var = res; }
void func1 (int res) { my_global_var = res+1; }

void (*pf[])(int res) = {func0, func1};

#if DESIGN_PATTERN == 0
void jumpTable(int c) // original jumptable function
{
    int res = 4;
    pf[c](res);
}
#else
void jumpTable(int c) // jump table funcion with design pattern applied
{
    int res = 4;
    switch (c) {
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


void jumpTable_test(int c)
{
    jumpTable(c);
}

int main(int argc, char *argv[])
{
    jumpTable_test(argc%2);

    return 0;
}
