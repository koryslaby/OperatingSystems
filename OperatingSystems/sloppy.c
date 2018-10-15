#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

#define NUMCPUS 6
long int total_differencesec = 0;
long int total_differencemsec = 0;

pthread_mutex_t tlock;

typedef struct __counter_t {
	int global;
	pthread_mutex_t glock;
	int local[NUMCPUS];
	pthread_mutex_t llock[NUMCPUS];
	int threshold;
}counter_t;

typedef struct _thread_data {
	int id;
}thread_data;


void init(counter_t *c, int threshold){
	c->threshold = threshold;
	c->global = 0;
	pthread_mutex_init(&c->glock, NULL);
	int i;
	for (int i = 0; i < NUMCPUS; ++i)
	{
		c->local[i] = 0;
		pthread_mutex_init(&c->llock[i], NULL);
	}
}

void update(counter_t *c, int threadID, int amt){
	int cpu = threadID % NUMCPUS;
	pthread_mutex_lock(&c->llock[cpu]);
	c->local[cpu] += amt;
	if (c->local[cpu] >= c->threshold)
	{
		pthread_mutex_lock(&c->glock);
		c->global += c->local[cpu];
		pthread_mutex_unlock(&c->glock);
		c->local[cpu] = 0;
	}
	pthread_mutex_unlock(&c->llock[cpu]);
}

int get(counter_t *c){
	pthread_mutex_lock(&c->glock);
	int val = c->global;
	int thes = c->threshold;
	pthread_mutex_unlock(&c->glock);
	return val;
}

counter_t mycounter;
void *myThread(void *vargp){
	thread_data *id = vargp;
	struct timeval tv1;
	struct timeval tv2;
	int start_time = gettimeofday(&tv1, NULL);
	pthread_mutex_lock(&tlock);
	for ( long long int i = 0; i < 1000000; ++i)
	{
		update(&mycounter, id->id, 1);
	}
	int end_time = gettimeofday(&tv2, NULL);
	long int difference_sec = tv2.tv_sec - tv1.tv_sec;
	long int difference_msec = tv2.tv_usec - tv1.tv_usec;
	total_differencesec += difference_sec;
	total_differencemsec += difference_msec;

	printf("%s\n", "------------------------------------");
	printf("%s%d%s\n", "thread", id->id, " (seconds)" );
	printf("%s%ld\n", "time took to update single thread(seconds): ", difference_sec );
	printf("%s%ld\n", "total time is(seconds):", total_differencesec);
	printf("%s\n",  "(microseconds)" );
	printf("%s%ld\n", "time took to update single thread(microseconds): ", difference_msec );
	printf("%s%ld\n", "total time is(msec):", total_differencemsec);

	pthread_mutex_unlock(&tlock);
	return NULL;
}

int main(int argc, char const *argv[])
{


	int threshold = 10;
	if (argc > 1)
	{
		threshold = atoi(argv[1]);
		printf("%s%d\n", "threshold is: ", threshold );
	}else {
		printf("%s%d\n", "default threshold is: ", threshold );
	}
	

	int threads = NUMCPUS;

	thread_data thread1;
	thread_data thread2;
	thread_data thread3;
	thread_data thread4;
	thread_data thread5;
	thread_data thread6;
	thread_data *pointer;
	

	

	pthread_t thread_id;
	init(&mycounter, threshold );
	
	for (int i = 0; i < threads; ++i)
	{
		switch(i){
			case 0:
			pointer = &thread1;
			break;
			case 1:
			pointer = &thread2;
			break;
			case 2:
			pointer = &thread3;
			break;
			case 3:
			pointer = &thread4;
			break;
			case 4:
			pointer = &thread5;
			break;
			case 5:
			pointer = &thread6;
			break;
		}
		pointer->id = (i+1);
		pthread_create(&thread_id, NULL, myThread, pointer);
	}
	pthread_exit(NULL);
	return 0;
}