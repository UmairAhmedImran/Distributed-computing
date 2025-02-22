#include <stdio.h>
#include <pthread.h>


pthread_cond_t c = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *thread_function(void *arg) {
	pthread_mutex_lock(&m);
	pthread_cond_wait(&c, &m);
	printf("Thread resumed execution after signal.\n");
	pthread_mutex_unlock(&m);
	return NULL;
}

int main() {
	pthread_t t;
	pthread_create(&t, NULL, thread_function, NULL);

	sleep(1);
	pthread_mutex_lock(&m);
	pthread_cond_signal(&c);
	pthread_mutex_unlock(&m);

	pthread_join(t, NULL);
	return 0;

}
