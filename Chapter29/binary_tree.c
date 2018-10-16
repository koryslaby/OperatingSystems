#include <stddef.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

//creating a structure of type node that will later make up my tree.
typedef struct _node_t 
{
	int id;
	int data;
	struct _node_t *left;
	struct _note_t *right;
	pthread_mutex_t nlock;
}node_t;

typedef struct _Tree
{
	node_t *root;
}Tree;

void Tree_init(Tree *T, node_t *R)
{
	T->root = R;
}

void Node_init(node_t *N) 
{
	N->data = 0;
	N->left = NULL;
	N->right = NULL;
	pthread_mutex_init(&N->nlock, NULL);
}

void add_children(node_t *P, node_t *L, node_t *R)
{
	Node_init(L);
	Node_init(R);
	P->left = L;
	P->right = R;
	L = malloc(sizeof(node_t));
	R = malloc(sizeof(node_t));
}

void incrument(node_t *S) 
{
	pthread_mutex_lock(&S->nlock);
	S->data++;
	pthread_mutex_unlock(&S->nlock);
	return;
}

//used to search through the tree and incrument each nodes data value
//by 10.
void search(node_t *R, Tree *T)
{
	for (int i = 0; i < 10; ++i)
	{
		incrument(R);
	}

	if (R->left != NULL)
	{
		search(R->left, T);
	}
	if (R->right != NULL) {
		search(R->right, T);
	}else{
		return;
	}
}

//each thread runs from this and its performance is based of how fast it can
//get through the tree and incrument each node 10 times.
void *myThread(void *vargp)
{
	printf("%s\n", "thread is created" );
	struct timeval tv1;
	struct timeval tv2;
	int performance;
	Tree *myTree = vargp;
	node_t *root = myTree->root;
	int start_time = gettimeofday(&tv1, NULL);
	search(root, myTree);
	int end_time = gettimeofday(&tv2, NULL);
	performance = tv2.tv_usec - tv1.tv_usec;
	printf("%s%d\n", "time took to run through Tree is: ", performance);
	return NULL;

}


int main(int argc, char const *argv[])
{
	//instancing each node.
	Tree myTree;
	node_t root;
	Node_init(&root);
	Tree_init(&myTree, &root);
	node_t node1;
	node_t node2;
	node_t node3;
	node_t node4;
	node_t node5;
	node_t node6;
	node_t node7;
	node_t node8;
	node_t node9;
	node_t node10;
	node_t node11;
	node_t node12;
	node_t *itter;

	//assigning an id to each node.
	node1.id = 1;
	node2.id = 2;
	node3.id = 3;
	node4.id = 4;
	node5.id = 5;
	node6.id = 6;
	node7.id = 7;
	node8.id = 8;
	node9.id = 9;
	node10.id = 10;
	node11.id = 11;
	node12.id = 12;

	//constructiong the tree.
	add_children(&root, &node1, &node2);
	add_children(&node1, &node3, &node4);
	add_children(&node2, &node5, &node6);
	add_children(&node3, &node7, &node8);
	add_children(&node4, &node9, &node10);
	add_children(&node5, &node11, &node12);

	//taking command line input if there are any.
	int threads_creat = 4;

	if (argc > 1)
	{
		if (*argv[1] == 'h')
		{
			printf("%s\n\n","if you don't want the default" );
			printf("%s\n", "executable threads_creat" );
			return 0;
		}
		threads_creat = atoi(argv[1]);
		printf("%s%d\n", "Threads to create is: ", threads_creat);
	}else {
		printf("%s%d\n", "default Threads: ", threads_creat );
	}

	//creating how ever many threads are specified.
	pthread_t threadID;
	for (int i = 0; i < threads_creat; ++i)
	{
		pthread_create(&threadID, NULL, myThread, &myTree);
	}
	pthread_exit(NULL);



	return 0;
}