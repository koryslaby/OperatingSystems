#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

typedef struct _counter_t{
	int value;
}counter_t;

void init(counter_t *c) {
	c->value = 0;
}

void incrument(counter_t *c){
	c->value++;
}

void decrement(counter_t *c){
	c->value--;
}

int get(counter_t *c){
	return c->value;
}

counter_t mycounter;
void *myThread(void *vargp){
	printf("%s\n", "thread is created");
	incrument(&mycounter);
	return NULL;
}

int main(int argc, char const *argv[])
{
	int threads = 10;
	if (argc > 1)
	{
		threads = atoi(argv[1]);
		printf("%s%d\n", "threads to be created is: ", threads );
	}
	struct timeval tv1;
	struct timeval tv2;
	pthread_t thread_id;
	
	printf("%s\n", "creating thread");
	int start_time = gettimeofday(&tv1, NULL);
	for (int i = 0; i < threads; ++i)
	{
		pthread_create(&thread_id, NULL, myThread, (void *)&thread_id);
	}
	int end_time = gettimeofday(&tv2, NULL);
	printf("%s\n", "after creating threadstha" );

	long int difference = tv2.tv_usec - tv1.tv_usec;

	printf("%s%ld\n", "time took to incrument is: ", difference);
	printf("%s%d\n", "the counter is at ", get(&mycounter) );
	


	
	return 0;
}