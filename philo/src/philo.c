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

#include "philo.h"

bool take_a_fork(t_data_philo *data)
{
	pthread_mutex_lock(&data->all_data->mutex);
	if (!data->all_data->fork[data->id])
		data->all_data->fork[data->id] = 1;
	else
	{
		pthread_mutex_unlock(&data->all_data->mutex);
		return (0);
	}
	if (!data->all_data->fork[(data->id + 1)
		% data->all_data->number_of_philosophers])
		data->all_data->fork[(data->id + 1)
			% data->all_data->number_of_philosophers] = 1;
	else
	{
		pthread_mutex_unlock(&data->all_data->mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->all_data->mutex);
	printf("%ld %i has taken a fork\n", 
		current_time(data->all_data->init_timeval), data->id);
	return (1);
}

void	is_eating(t_data_philo *data)
{
	if (data->all_data->number_of_times_each_philosopher_must_eat > 0)
	{
		pthread_mutex_lock(&data->all_data->mutex);
		data->all_data->number_of_times_each_philosopher_must_eat--;
		pthread_mutex_unlock(&data->all_data->mutex);
	}
	printf("%ld %i is eating\n", current_time(data->all_data->init_timeval), data->id);
	data->all_data->time_without_eat = 0;
	usleep(data->all_data->time_to_eat);
	data->all_data->fork[data->id] = 0;
	data->all_data->fork[(data->id + 1) % data->all_data->number_of_philosophers] = 0;
	if (data->all_data->number_of_times_each_philosopher_must_eat == 0)
	{
		data->all_data->is_dead = true;
	}
}

void	is_sleeping(t_data_philo *data)
{
	printf("%ld %i is sleeping\n", 
		current_time(data->all_data->init_timeval), data->id);
	usleep(data->all_data->time_to_sleep);
}

void	*philo_thread(void *arg_data)
{
	t_data_philo	*data;

	data = (t_data_philo *)arg_data;
	while (true)
	{
		if (data->all_data->time_without_eat > data->all_data->time_to_die)
		{
			printf("%ld %i died\n",
				current_time(data->all_data->init_timeval), data->id);
			data->all_data->is_dead = true;
		}
		if (data->all_data->is_dead)
			return ((void *)"0");



		if (take_a_fork(data))
		{
			is_eating(data);
			is_sleeping(data);
		}
		printf("%ld %i is thinking\n",
			current_time(data->all_data->init_timeval), data->id);

		data->all_data->time_without_eat = current_time(data->all_data->init_timeval);


		printf("{%d}\n", data->all_data->time_without_eat);
		// if (data->id == 0)
		// 	printf("\033[90m%ld\033[m\n", current_time(data->all_data->init_timeval));
		// if (data->id == 1)
		// 	printf("\033[91m%ld\033[m\n", current_time(data->all_data->init_timeval));
		// if (data->id == 2)
		// 	printf("\033[92m%ld\033[m\n", current_time(data->all_data->init_timeval));
		// if (data->id == 3)
		// 	printf("\033[93m%ld\033[m\n", current_time(data->all_data->init_timeval));
		// if (data->id == 4)
		// 	printf("\033[94m%ld\033[m\n", current_time(data->all_data->init_timeval));
	
		usleep(1);
	}
	return ((void *)"0");
}

void	master(int ac, char **av, t_data_philo *data)
{
	int	i;

	i = 0;
	init_data_philo(&data, ac, av);
	pthread_mutex_init(&data[0].all_data->mutex, NULL);
	while (i < data[0].all_data->number_of_philosophers)
	{
		pthread_create(&data[0].all_data->thread[i], NULL,
			philo_thread, (void *)&data[i]);
		i++;
	}
	i = 0;
	while (i < data[0].all_data->number_of_philosophers)
	{
		pthread_join(data[0].all_data->thread[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&data[0].all_data->mutex);
	free_all_data(data[0].all_data);
	free(data);
}

int	main(int ac, char **av)
{
	int				i;
	int				n;
	t_data_philo	data;

	i = 1;
	n = 1;
	if (ac == 6 || ac == 5)
	{
		while (av[i] && n)
		{
			n = str_isdigit(av[i]);
			i++;
		}
		if (n == 0)
			error();
		master(ac, av, &data);
	}
	else
		error();
	return (0);
}
