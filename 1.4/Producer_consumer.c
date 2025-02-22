#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_producer = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_consumer = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
	int item = 0;
	while (1) {
		pthread_mutex_lock(&mutex);

		while (count == BUFFER_SIZE) {
			pthread_cond_wait(&cond_producer, &mutex);
		}
		buffer[count++] = item++;
		printf("Produced: %d\n", item);

		pthread_cond_signal(&cond_consumer);
		pthread_mutex_unlock(&mutex);

		sleep(1);
	}
}

void *consumer(void *arg) {
	while(1) {
		pthread_mutex_lock(&mutex);

		while (count == 0) {
			pthread_cond_wait(&cond_consumer, &mutex);
		}

		int item = buffer[--count];
		printf("Consumed: %d\n", item);

		pthread_cond_signal(&cond_producer);
		pthread_mutex_unlock(&mutex);

		sleep(2);
	}
}

int main() {
	pthread_t prod, cons;

	pthread_create(&prod, NULL, producer, NULL);
	pthread_create(&cons, NULL, consumer, NULL);

	pthread_join(prod, NULL);
	pthread_join(cons, NULL);

	return 0;
}
