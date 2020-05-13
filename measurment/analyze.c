#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define SAMPLING_RATE_MHZ 24.0

int main(int argc, char *argv[])
{
	char line[512];
    int value=0, value_old=0;
    unsigned long ticks=0;

    FILE *fp = fopen(argv[1], "r");

    printf("usec\n");

    while (fgets(line, 512, fp))
	{
        value = atoi(line);
        //printf("%ld\n", value);

        if(value != value_old && value == 1) // rising Edge
        {
            ticks=0;
        }

        if(value == 1)
        {
            ticks++;
        }

        if(value != value_old && value == 0) // falling Edge
        {
            double usec;

            usec = (double)ticks / SAMPLING_RATE_MHZ;
            printf("%f\n", usec);
        }

        value_old=value;
	}

    fclose(fp);
}