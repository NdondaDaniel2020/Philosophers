#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>

int main()
{
	int				i;
	long			re;		
    struct timeval	tv;
    struct timeval	init_tv;
    
	i = 0;
    gettimeofday(&init_tv, NULL);
    while (true)
    {

        gettimeofday(&tv, NULL);

		printf("time a: %i\n", (tv.tv_sec - init_tv.tv_sec));
		printf("time (-)*1000: %i\n", ((tv.tv_sec - init_tv.tv_sec) * 1000));
		printf("time u: %i\n", tv.tv_usec);
		printf("time u/1000: %i\n", (tv.tv_usec / 1000));
		printf("time (+): %i\n\n\n", ((tv.tv_sec - init_tv.tv_sec) * 1000) + (tv.tv_usec / 1000));
		usleep(2000);
    }
    return 0;
}