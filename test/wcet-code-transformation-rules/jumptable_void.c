#define DESIGN_PATTERN 1

// void returning jumtables can't be analyzed!?
void func0 (void) { ; }
void func1 (void) { ; }

void (*pf[])(void) = {func0, func1};

#if DESIGN_PATTERN == 1
// jump table with design pattern applied
void jumpTableVoid(int c)
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
#else
// original jumptable function
void jumpTableVoid(int c)
{
    pf[c]();
}
#endif


void jumpTableVoid_test(int c)
{
    jumpTableVoid(c);
}

int main(int argc, char *argv[])
{
    jumpTableVoid_test(argc%2);

    return 0;
}
