#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
	long int old = 0;

	if(argv[1] == "-h") {
			printf("%s\n", "Set up like 'programe.exe PAGESIZE NUMPAGES'" );
		return 0;
	}

	if (argc < 3)
	{
		printf("%s\n", "Set up like 'programe.exe PAGESIZE NUMPAGES'");
		return 0;
	}else {
		//gets(argv[1]);
		//gets(argv[2]);
		const int PAGESIZE = atoi(argv[1]);
		const int NUMPAGES = atoi(argv[2]);

		struct timeval tv1;
		struct timeval tv2;

		int start_time = gettimeofday(&tv1, NULL);

		int jump = (PAGESIZE / sizeof(int));

		printf("%s%d\n", "jump is ", jump );
		printf("%s%d\n", "PAGESIZE is ",  PAGESIZE );
		printf("%s%d\n", "NUMPAGES is ", NUMPAGES );
		for (int i = 0; i < NUMPAGES * jump; i += jump)
		{
			printf("%s%d\n", "one iteration i is ", i );
			int run_time = gettimeofday(&tv2, NULL);
			printf("%s%ld\n", "tv2.tv_usec is ",  tv2.tv_usec );
			printf("%s%ld\n", "tv1.tv_usec is ", tv1.tv_usec );
			long int difference = tv2.tv_usec - tv1.tv_usec;
			printf("%ld\n", difference);

			if (i > 0)
			{
				old = difference - old;
				printf("%s%ld\n", "time since last check",  old );
				old = difference;
			}else {
				old = difference;
			}
		}
	}
	
	return 0;
}