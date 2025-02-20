
/// Threads.c 1.2.1
#include <stdio.h>
#include <pthread.h>

void *mythread(void* args) {
   printf("Hello from %s\n", (char*) args);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p1; // initialize threads
    printf("main begin\n");
    pthread_create(&p1, NULL, mythread, "A"); // (thread type *thread, attributes type *attr, function type *start_routine, void *arg) // create thread p1
    pthread_join(p1, NULL); // (thread type *thread, return value) // wait for thread p1 to finish
    printf("main end\n");
    return 0;
}

