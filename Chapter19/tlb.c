#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
	long int old = 0;

	if(argv[1] == "-h") {
			printf("%s\n", "Set up like 'programe.exe numpagetouch numoftrials'" );
		return 0;
	}

	if (argc < 3)
	{
		printf("%s\n", "Set up like 'programe.exe numpagetouch numoftrials'");
		return 0;
	}else {
		//gets(argv[1]);
		//gets(argv[2]);
		const int PAGESIZE = getpagesize();
		const long int NUMPAGES = 15;
		int elems = 0;

		int numpagetouch = atoi(argv[1]);
		int numoftrials = atoi(argv[2]);

		elems = (PAGESIZE * numpagetouch) / sizeof(int);

		int *tlb = (int*) calloc(elems, sizeof(int));

		struct timeval tv1;
		struct timeval tv2;

		int jump = (PAGESIZE / sizeof(int));

		for (int x = 0; x < numoftrials; x++)
		{
			printf("%s%d%s\n", "-------------------starting trial: ", x , "---------------------" );
			int start = gettimeofday(&tv1, NULL);
			for (long int i = 0; i < (numpagetouch * jump); i += jump)
			{
				//printf("%s%ld\n", "accessing page: ", (i/jump));
				tlb[i] += 1;
				
			}
			int end = gettimeofday(&tv2, NULL);
			printf("%s%ld\n", "nanosecs to accessing pages: ", (tv2.tv_usec-tv1.tv_usec));
		}
		free(tlb);


	}
	
	return 0;
}