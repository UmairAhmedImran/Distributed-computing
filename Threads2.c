
/// Threads.c 1.2.2
#include <stdio.h>
#include <pthread.h>

static volatile int counter = 0;

void *mythread(void* args) {
    printf("%s: begin\n", (char*) args);
    int i;
    for (i = 0; i < 1e7; i++) {
        counter = counter + 1;
    }
    printf("%s: done\n", (char*) args);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2; // initialize threads
    printf("main: begin (counter = %d)\n", counter);
    pthread_create(&p1, NULL, mythread, "A");   // create thread p1
    pthread_create(&p2, NULL, mythread, "B");   // create thread p2
    pthread_join(p1, NULL); // wait for thread p1 to finish
    pthread_join(p2, NULL); // wait for thread p2 to finish
    printf("main: done with both (counter = %d)\n", counter);
    return 0;
}

/*
    Why Does This Happen?

This is due to a race condition. A race condition occurs when multiple threads access and modify a shared variable concurrently without proper synchronization, leading to unpredictable results.
What’s Happening Under the Hood?

    The operation counter = counter + 1 is not atomic. It involves three steps:

        Read the current value of counter.

        Increment the value by 1.

        Write the new value back to counter.

    When two threads run simultaneously, they may interleave these steps. For example:

        Thread A reads counter = 100.

        Thread B reads counter = 100.

        Thread A increments and writes counter = 101.

        Thread B increments and writes counter = 101.

        The final value is 101, even though two increments were performed.

    This interleaving happens millions of times, causing the final value of counter to be much lower than expected.main: begin (counter = 0)
*/