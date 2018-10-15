#include <stddef.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define NUMCPU 6


typedef struct _node_t {
	int key;
	struct _node_t *next;
}node_t;

typedef struct _list_t {
	node_t *head;
	pthread_mutex_t lock;
}list_t;

void Node_init(node_t *N) {
	N->key = 0;
	N->next = NULL;
}

void List_init(list_t *L) {
	L->head = NULL;
	pthread_mutex_init(&L->lock, NULL);
}

void List_Insert(list_t *L, int key) {
	node_t *new = malloc(sizeof(node_t));
	if (new == NULL)
	{		
		perror("malloc");
		return;
	}
	new->key = key;

	pthread_mutex_lock(&L->lock);
	new->next = L->head;
	L->head = new;
	pthread_mutex_unlock(&L->lock);
}

int List_Lookup(list_t *L, int key) {
	int rv = -1;
	pthread_mutex_lock(&L->lock);
	node_t *curr = L->head;
	while(curr) {
		if (curr->key == key)
		{
			rv = 0;
			break;
		}
		curr = curr->next;
	}
	pthread_mutex_unlock(&L->lock);
	return rv;
}

void *myThread(void *vargp)
{
	struct timeval tv1;
	struct timeval tv2;
	int performance;
	list_t *myList = vargp;
	int start_time = gettimeofday(&tv1, NULL);
	List_Lookup(myList, 0);
	int end_time = gettimeofday(&tv2, NULL);
	performance = tv2.tv_usec - tv1.tv_usec;
	printf("%s%d\n", "time took to run through list is: ", performance);
	return NULL;
}


int main(int argc, char const *argv[])
{
	//Declaring variables
	int list_length = 10;
	int threads_creat = NUMCPU;
	node_t start;
	list_t myList;
	List_Insert(&myList, 0);

	//If there is command line input it is assigned to the correct
	//variables. The user is informed what the list length and 
	//threads created are.

	//./executable list_length threads_creat

	if (argc > 1)
	{
		if (*argv[1] == 'h')
		{
			printf("%s\n\n","if you don't want the defaults" );
			printf("%s\n", "executable list_length threads_creat" );
			return 0;
		}
		list_length = atoi(argv[1]);
		printf("%s%d\n", "list_length is: ", list_length);
	}else {
		printf("%s%d\n", "default list_length is: ", list_length );
		printf("%s%d\n", "default Threads: ", NUMCPU );
	}
	if(argc == 3)
	{
		printf("%s\n", "changing threads_creat" );
		threads_creat = atoi(argv[2]);
		printf("%s%d\n", "Threads to be created is: ", threads_creat);
	} 


	for (int i = 0; i < list_length; ++i)
	{
		List_Insert(&myList, i);
	}

	printf("%s%d\n", "threads_creat is: ", threads_creat);
	//Creating thread and looking for the first node.

	pthread_t threadID;

	for (int i = 0; i < threads_creat; ++i)
	{
		pthread_create(&threadID, NULL, myThread, &myList);
	}
	pthread_exit(NULL);

	return 0;
}