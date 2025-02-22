// These include necessary libraries for input/output and thread operations.
#include <stdio.h>
#include <pthread.h>

// Defines a structure myarg_t with three integer members: a, b, and c
// This will be used to pass multiple parameters to the thread
typedef struct {
	int a;
	int b;
	int c;
} myarg_t;

// This is the function that will run in the new thread
//Takes a void* parameter (standard for pthread functions)
//Casts the generic pointer to our myarg_t struct type
//Prints the three integer values
//Returns NULL (threads can return a value, but we're not using it here)

void *mythread(void* arg) {
	myarg_t *args = (myarg_t *) arg;
	printf("%d %d %d\n", args->a, args->b, args->c);
	return NULL;
}

//pthread_t p: Declares a thread identifier
//Creates a struct instance with values 10, 20, 30
//pthread_create(): Creates a new thread
//
//    &p: Stores the thread ID
//    NULL: Uses default thread attributes
//    mythread: Function to execute
//    &args: Pointer to arguments passed to thread
//
//pthread_join(): Waits for the thread to finish
//Returns 0 to indicate successful program completion

int main(int argc, char *argv[]) {
	pthread_t p;
	myarg_t args = {10, 20, 30};
	pthread_create(&p, NULL, mythread, &args);
	pthread_join(p, NULL);
	return 0;
}
