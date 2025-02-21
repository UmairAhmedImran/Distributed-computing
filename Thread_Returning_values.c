#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct { int a; int b; } myarg_t;
typedef struct { int x; int y; } myret_t;

void *mythread(void* args) {
	myret_t *rvals = malloc(sizeof(myret_t));
	rvals->x = 1;
	rvals->y = 2;
	return (void*) rvals;
}

// case of using local variable which is wrong
//There’s also a commented-out version of mythread that’s worth a quick peek. It shows a common mistake: creating a local myret_t variable (oops) on the stack and returning its address. That would be bad because stack memory gets cleaned up when the function exits, leaving the main program with a dangling pointer. The active version avoids this trap by using malloc.
//void *mythread(void* arg) {
//	myarg_t *args = (myarg_t *) args;
//	printf("%d %d\n", args->a, args->b);
//	myret_t oops;
//	oops.x = 1;
//	oops.y = 2;
//	return (void *) &oops;
//}

int main(int argc, char *argv[]){
	pthread_t p;
	myret_t *rvals;
	myarg_t args = {10, 20};
	pthread_create(&p, NULL, mythread, &args);
	pthread_join(p, (void**) &rvals);
	printf("returned %d %d\n", rvals->x, rvals->y);
	free(rvals);
	return 0;
}

//The code uses <stdio.h>, <pthread.h>, and <stdlib.h> for printing, threads, and memory management. It defines two structs: myarg_t with a and b for input, and myret_t with x and y for output.
//
//The mythread function takes a void* argument (unused here), allocates a myret_t struct with malloc, sets x = 1 and y = 2, and returns it as a void*. The commented-out version shows a mistake—returning a stack variable’s address, which would fail.
//
//In main, we create a thread with pthread_create, passing a myarg_t struct initialized to {10, 20} (though it’s ignored). We use pthread_join to wait for the thread and get its return value into rvals, then print "returned 1 2" from rvals->x and rvals->y. Finally, we free(rvals) and exit.
