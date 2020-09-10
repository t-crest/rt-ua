#include <stdio.h>
#include <stdlib.h>

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
    simple_function();
}

void recurse_infinite()
{
    recurse_infinite();
}

void recurse_counter(int i)
{
    if(i>0) recurse_counter(--i);
}

void simple_function()
{
}
/*
int simple_function(int n)
{
    int i, x=1;
    for(i=0;i<n;i++)
    {
        x=2*x;
    }
    return x;
}
 */
int simple_function_wcet(int n)
{
    int i, x=1;

    if(n>=5) return -1;
    #pragma loopbound min 0 max 5
    for(i=0;i<n;i++)
    {
        x=x+i;
    }
    return x;
}

int main()
{
    //simple_function();
    //recurse_function_loop1();
    //recurse_infinite();
    //recurse_counter(10);
    simple_function_wcet(1);
    return 0;
}
