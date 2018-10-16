#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sched.h>
#define _GNU_SOURCE

int main(int argc, char *argv[])
{
	cpu_set_t cpuset;
	CPU_SET(0, &cpuset);

	int size_of_page = getsizeofpage();
	

	printf("%d\n", CPU_COUNT() );
	printf("%s%d\n", size_of_page );
	return 0;
}