#include <stdio.h>
#include <pthread.h>

static int shared_counter = 0;
pthread_mutex_t lock; // Declare a mutex

void *increment_counter(void *arg) {
	for (int i = 0; i < 100000; i++) {
		pthread_mutex_lock(&lock); // lock the mutex
		shared_counter++; // Critical section
		pthread_mutex_unlock(&lock); // unlock the mutex
	}
	return NULL;
}

int main() {
	pthread_t t1, t2;

	// Initialize the mutex
	pthread_mutex_init(&lock, NULL);

	// Create two threads
	pthread_create(&t1, NULL, increment_counter, NULL);
	pthread_create(&t2, NULL, increment_counter, NULL);

	// Wait for thread to finish
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	//Destroy the mutex
	pthread_mutex_destroy(&lock);

	printf("Final counter value: %d\n", shared_counter);
	return 0;
}


//Documentation
//
//    pthread_mutex_init(&lock, NULL): Initializes the mutex.
//
//    pthread_mutex_lock(&lock): Locks the mutex. If the mutex is already locked, the thread will block until it is unlocked.
//
//    pthread_mutex_unlock(&lock): Unlocks the mutex.
//
//    pthread_mutex_destroy(&lock): Destroys the mutex when it is no longer needed.
