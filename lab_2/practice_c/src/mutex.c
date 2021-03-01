#include <stdio.h>
#include <pthread.h>

int global_variable = 0;

void* increment_global_var(void* mutex_pointer)
{
    int increment_count, delay_count;

    mutex_pointer = (pthread_mutex_t*) mutex_pointer;

    for(increment_count = 0; increment_count < 10; ++increment_count)
    {
        // critical section
        pthread_mutex_lock(mutex_pointer);
        ++global_variable;

        // delay
        for(delay_count = 0; delay_count < 5000000; ++delay_count);

        pthread_mutex_unlock(mutex_pointer);

        printf("%d ", global_variable);
        fflush(stdout);
    }
}

int main()
{
    pthread_t thread1, thread2;
    int return1, return2;

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    return1 = pthread_create(&thread1, NULL, increment_global_var, (void*) &mutex);
    return2 = pthread_create(&thread2, NULL, increment_global_var, (void*) &mutex);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);
    printf("\n");
    return 0;
}
