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

// void	init_data_philo(t_data_philo *data, int ac, char **av)
// {
// 	int					i;
// 	t_all_data_philo	all_data;

// 	i = 0;
// 	init_all_data_philo(&all_data, ac, av);
// 	data = malloc(sizeof(t_data_philo) * ac);
// 	pthread_mutex_init(&all_data.mutex, NULL);
// 	while (i < all_data.number_of_philosophers)
// 	{
// 		data[i].id = i;
// 		data[i].all_data = &all_data;
// 		pthread_create(&all_data.thread[i], NULL, philo_thread, (void *)&data[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < all_data.number_of_philosophers)
// 	{
// 		pthread_join(all_data.thread[i], NULL);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&all_data.mutex);
// 	free_data(data);
// }
