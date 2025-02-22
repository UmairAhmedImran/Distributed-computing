#include <stdio.h>
#include <pthread.h>

volatile int done = 0;

void *child(void *arg) {
	printf("Child\n");
	done = 1;
	return NULL;
}

int main(int argc, char *argv[]) {
	printf("parent: begin\n");
	pthread_t c;
	pthread_create(&c, NULL, child, NULL);
	while (done == 0) 
		; // spin
	printf("parent: end\n");
	return 0;
}

//Issues with Mutex Locks
//Locks provide basic synchronization (mutual exclusion) which does not work in all cases (as discussed in last slide)
//Spin waiting wastes a lot of CPU cycles
//What if a thread wanted to wait for a condition?
//
//Solution
//Condition variables
//
