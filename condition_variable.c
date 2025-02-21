#include <stdio.h>
#include <pthread.h>

int ready = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // Mutex for synchronization
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; // Condition variable

void *producer(void *arg) {
	pthread_mutex_lock(&lock);
	ready = 1; // set the condition
	printf("Producer: Condition is ready\n");
	pthread_cond_signal(&cond); // Signal the consumer
	pthread_mutex_unlock(&lock);
	return NULL;	
}

void *consumer(void *arg) {
	pthread_mutex_lock(&lock);
	while (ready == 0) {
		printf("Consumer: waiting for condition\n");
		pthread_cond_wait(&cond, &lock); // wait for the signal
	}
	printf("Consumer: Condition met\n");
	pthread_mutex_unlock(&lock);
	return NULL;
}

int main() {
	pthread_t t1, t2;

	// Create consumer and producer threads
	pthread_create(&t1, NULL, consumer, NULL);
	pthread_create(&t2, NULL, producer, NULL);

	// Wait for threads to finish
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	// Destroy the condition variable and mutex
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&lock);

	return 0;

}

//
//Documentation
//
//    pthread_cond_init(&cond, NULL): Initializes the condition variable.
//
//    pthread_cond_wait(&cond, &lock): Waits for a signal on the condition variable. The mutex is automatically released while waiting and reacquired before the function returns.
//
//    pthread_cond_signal(&cond): Signals one waiting thread to wake up.
//
//    pthread_cond_destroy(&cond): Destroys the condition variable when it is no longer needed.
