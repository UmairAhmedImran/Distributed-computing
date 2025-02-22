/// Threads.c 1.2.1
#include <stdio.h>
#include <pthread.h>

void *mythread(void* args) {
    printf("%s\n", (char*) args);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2; // initialize threads
    printf("main begin\n");
    pthread_create(&p1, NULL, mythread, "A");   // create thread p1
    pthread_create(&p2, NULL, mythread, "B");   // create thread p2
    pthread_join(p1, NULL); // wait for thread p1 to finish
    pthread_join(p2, NULL); // wait for thread p2 to finish
    printf("main end\n");
    return 0;
}

