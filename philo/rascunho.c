/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:10:02 by nmatondo          #+#    #+#             */
/*   Updated: 2024/09/23 11:10:05 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>

/*
void	init_data_philo(t_data_philo *data, int ac, char **av)
{
	int					i;
	t_all_data_philo	all_data;

	i = 0;
	init_all_data_philo(&all_data, ac, av);
	data = malloc(sizeof(t_data_philo) * ac);
	pthread_mutex_init(&all_data.mutex, NULL);
	while (i < all_data.number_of_philosophers)
	{
		data[i].id = i;
		data[i].all_data = &all_data;
		pthread_create(&all_data.thread[i], NULL,
			philo_thread, (void *)&data[i]);
		i++;
	}
	i = 0;
	while (i < all_data.number_of_philosophers)
	{
		pthread_join(all_data.thread[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&all_data.mutex);
	free_data(data);
}
*/

long	current_time(struct timeval init_tv)
{
	long			re;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	re = ((tv.tv_sec - init_tv.tv_sec) * 1000)
		+ ((tv.tv_usec - init_tv.tv_usec) / 1000);
	return (re);
	
}

int	main(void)
{
	long			re;
	struct timeval	init_tv;

	gettimeofday(&init_tv, NULL);
	while (true)
	{
		printf("%ld\n", current_time(init_tv));
	}
	return (0);
}


// printf("{cur_time [%ld] - data->last_meal_time [%ld] == [%ld]}\n", cur_time, data->last_meal_time, cur_time - data->last_meal_time);
// printf("{time_without_eat [%ld] > time_to_die [%d]}\n", data->time_without_eat, data->all_data->time_to_die);
// printf("{time_without_eat [%ld] > time_to_die [%d]}\n", (data->time_without_eat - 1), data->all_data->time_to_die);
