#include <stdio.h>
#include <stdint.h>
#include <machine/rtc.h>

#define MAX 32
 
uint32_t top=-1,stack[MAX];
void push(uint32_t v);
uint32_t pop();

void push(uint32_t v)
{
	if(top==MAX-1)
	{
		//printf("Stack is full!\n");
	}
	else
	{
		top=top+1;
		stack[top]=v;
	}
}
 
uint32_t pop()
{
	if(top==-1)
	{
		//printf("Stack is empty!\n");
	}
	else
	{
        return stack[top--];
	}
}

void iter(uint32_t b, uint32_t e, uint32_t *ret)
{
    int pow=1;

    if(e>MAX) {*ret=0; return;}

    _Pragma("loopbound min 0 max MAX")
    for(uint32_t i=0;i<e;i++)
        pow=pow*b;

    *ret = pow;
}

void rec(uint32_t b, uint32_t e, uint32_t *ret)
{
    uint32_t pow=1;

    if(e>MAX) {*ret=0; return;}

    _Pragma("loopbound min 0 max MAX")
    for(uint32_t i=e;i>0;i--)
        push(b);

    _Pragma("loopbound min 0 max MAX")
    for(uint32_t i=e;i>0;i--)
        pow=pow*pop();

    *ret = pow;
}

void (*pw[])(uint32_t b, uint32_t e, uint32_t *ret) = {iter, rec};

uint32_t calc_pow(uint32_t b, uint32_t e, uint32_t t, uint64_t *diff)
{
    uint64_t start, end;
    start=get_cpu_usecs();
    uint32_t ret = 0;
    pw[t](b, e, &ret);
    end=get_cpu_usecs();
    *diff=end-start;

    return ret;
}

int main(void)
{
    uint64_t diff_iter, diff_rec;
    for(int i=0;i<100;i++){
    uint32_t ret_iter=calc_pow(2, 30, 0, &diff_iter);
    uint32_t ret_rec=calc_pow(2, 30, 1, &diff_rec);
    printf("diff_iter: %lld usec result=%lu\n", diff_iter, ret_iter);
    printf("diff_rec: %lld usec result=%lu\n", diff_rec, ret_rec);}
    return 0;
}

/* TODO
    recursive auf stack
    clock_gettime auf get_cpu_usecs 
    wcet berechnen
*/
