#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>

int main()
{
	long			re;		
    struct timeval	tv;
    struct timeval	init_tv;

    gettimeofday(&init_tv, NULL);
    while (true)
    {
        gettimeofday(&tv, NULL);
		re = ((tv.tv_sec - init_tv.tv_sec) * 1000)
			+ ((tv.tv_usec - init_tv.tv_usec) / 1000);
		printf("%ld\n", re);
    }
    return 0;
}