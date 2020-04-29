#include <stdio.h>

#define DESIGN_PATTERN 0
#define DEBUG 0
#define MTU 60

int send(int buf_length)
{
    if(buf_length > MTU) buf_length = MTU;

    #if DEBUG
    printf("sending %i bytes...\n", buf_length);
    #endif
    return buf_length;
}

// original for loop function
int while_loop(int buf_length)
{
    int n, nWritten = 0, nRemain = buf_length;

    while (nWritten < buf_length) {
        n = send(nRemain);
        if(n == -1)
            return -1;

        nWritten += n;
        nRemain -= n;
    }
    return nWritten;
}

// for loop with design pattern applied
int while_loop_dp(int buf_length)
{
    int n, nWritten = 0, nRemain = buf_length;

    _Pragma("loopbound min 1 max 1")  // data must be send in one packet
    while (nWritten < buf_length) {
        n = send(nRemain);
        if(n == -1)
            return -1;
        
        if(n != buf_length) return -1;  // break condition if data can't be send in one packet

        nWritten += n;
        nRemain -= n;
    }
    return nWritten;
}

void while_loop_test()
{
    int buf_length = 60;
    int ret = -1;

    #if DESIGN_PATTERN
        ret = while_loop_dp(buf_length);
    #else
        ret = while_loop(buf_length);
    #endif

    #if DEBUG
    if(ret == -1) printf("send error\n");
    else printf("%i bytes send\n", ret);
    #endif
}

int main(int argc, char *argv[])
{
    while_loop_test();

    return 0;
}