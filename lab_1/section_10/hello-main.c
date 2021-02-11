#include "hello.h"
#include <stdio.h>

void delay(int counter)
{
    int i;
    for(i = 0; i < counter; ++i); // wait
}

int main()
{
    printf("Hello World from main!\n");
    delay(0x5fffff);

    int count = 0;
    while(count < 1)
    {
        printf("press enter");
        if(getchar())
        {
            helloprint();
            count = incrementcount(count);
            printf("current count: %d\n", count);
        }
    }

    printf("Bye!\n");
    return 0;
}
