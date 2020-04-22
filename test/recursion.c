#include <stdio.h>
#include <stdlib.h>

void recurse_function_loop2();

void recurse_function_loop1()
{
    recurse_function_loop2();
}

void recurse_function_loop2()
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

 
int main()
{
    recurse_function_loop1();
    recurse_infinite(10);
    recurse_counter(10);
    return 0;
}