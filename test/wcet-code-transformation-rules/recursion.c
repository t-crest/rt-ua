#include <stdio.h>
#include <stdlib.h>


#ifndef APPLY_TRANSFORMATION_RULE
void recurse_function_loop2();
void recurse_function_loop3();
void simple_function();

void recurse_function_loop1()
{
    recurse_function_loop2();
}

void recurse_function_loop2()
{
    recurse_function_loop3();
}

void recurse_function_loop3()
{
    recurse_function_loop1();
}

void recurse_infinite()
{
    recurse_infinite();
}

void recurse_counter(int i)
{
    if(i>0) recurse_counter(--i);
}
#else
    // TODO
#endif

void recursion_test() 
{
    //recurse_function_loop1();
    //recurse_infinite();
    recurse_counter(10);
}

int main()
{
	recursion_test();
    return 0;
}
