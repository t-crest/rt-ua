#include <stdio.h>
#include <stdlib.h>

typedef void (*Handler)(void);

void function0 (void) { }
void function1 (void) { }
void function2 (void) { }

enum{
    F0,
    F1,
    F2
};

Handler jump_table[3] = {function0, function1, function2};
 
int main()
{
    jump_table[F0]();
    jump_table[F1]();
    jump_table[F2]();

    return 0;
}