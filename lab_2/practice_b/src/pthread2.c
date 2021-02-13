#include <stdio.h>
#include <pthread.h>

int global_variable = 0;

void* increment_global_var()
{
    int increment_count, delay_count;

    for(increment_count = 0; increment_count < 10; ++increment_count)
    {
        ++global_variable;

        // delay
        for(delay_count = 0; delay_count < 5000000; ++delay_count);

        printf("%d ", global_variable);
        fflush(stdout);
    }
}

int main()
{
    pthread_t thread1, thread2;
    int return1, return2;

    return1 = pthread_create(&thread1, NULL, increment_global_var, NULL);
    return2 = pthread_create(&thread2, NULL, increment_global_var, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\n");
    return 0;
}
