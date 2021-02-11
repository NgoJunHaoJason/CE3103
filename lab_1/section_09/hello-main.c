#include "hello.h"
#include <stdio.h>

int main()
{
    int count = 0;

    while(1)
    {
        printf("press enter");
        if(getchar())
        {
            helloprint();
            count = incrementcount(count);
            printf("current count: %d\n", count);
        }
    }
    return 0;
}
