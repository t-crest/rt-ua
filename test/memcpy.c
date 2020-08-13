#include <stdio.h>
#include <string.h>

#define DESIGN_PATTERN 1
#define DEBUG 1

// memcpy with design pattern applied
void* memcpy_dp(void * destination, const void * source, size_t num)
{
    int i, n = 0;
    char *src, *dst;

    src = (char*)source;
    dst = (char*)destination;

    if(num > 10) return NULL;   // check if num ist bigger then max loopbound

    _Pragma("loopbound min 1 max 10")  // maximum 10 for loop itterations
    for(i=0;i<num;i++)
    {
        dst[i] = src[i];
    }
    return destination;
}

void memcpy_test()
{
    char text[] = "Test";
    char text_dst[100];

    void* ret;

    #if DESIGN_PATTERN
        ret = memcpy_dp((void*)text_dst, (void*)text, 5);
    #else
        ret = memcpy((void*)text_dst, (void*)text, 5);
    #endif

    #if DEBUG
    printf("'%s'\n", text_dst);
    if(ret == NULL) printf("loopbound exceeded\n");
    #endif
}

int main(int argc, char *argv[])
{
    memcpy_test();

    return 0;
}