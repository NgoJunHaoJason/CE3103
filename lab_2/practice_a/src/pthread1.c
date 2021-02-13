// create 2 threads
// each prints its own message onto the screen

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_message(void* string_pointer)
{
    char* text;
    text = (char*) string_pointer;

    printf("%s\n", text);
    return NULL;
}

int main()
{
    pthread_t thread1, thread2;
    int return1, return2;

    char* message1 = "I am thread 1";
    char* message2 = "I am thread 2";

    return1 = pthread_create(&thread1, NULL, print_message, (void*) message1);
    return2 = pthread_create(&thread2, NULL, print_message, (void*) message2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("thread 1 return: %d, thread 2 return: %d\n", return1, return2);
    return 0;
}
