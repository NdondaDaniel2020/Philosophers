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

static void	check_if_any_philosophers_have_died(t_data_philo *data)
{
	long			cur_time;

	cur_time = current_time(data->all_data->init_timeval);
	pthread_mutex_lock(&data->all_data->mutex);
	data->time_without_eat = cur_time - data->last_meal_time;
	if (data->time_without_eat > data->all_data->time_to_die + 5)
	{
		if (!data->all_data->monitor)
		{
			print_menssage(data, "died");
			data->all_data->is_dead = true;
			data->all_data->monitor = true;
		}
	}
	pthread_mutex_unlock(&data->all_data->mutex);
}

static void	operation(t_data_philo *data, bool *think)
{
	if (take_a_fork(data))
	{
		*think = false;
		is_eating(data);
		is_sleeping(data);
	}
	else if (!think)
	{
		*think = true;
		print_menssage(data, "is thinking");
	}
}

static void	*philo_thread(void *arg_data)
{
	bool			think;
	t_data_philo	*data;

	think = false;
	data = (t_data_philo *)arg_data;
	while (true)
	{
		check_if_any_philosophers_have_died(data);
		pthread_mutex_lock(&data->all_data->mutex);
		if (data->all_data->is_dead)
		{
			pthread_mutex_unlock(&data->all_data->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&data->all_data->mutex);
		operation(data, &think);
	}
}

static void	master(int ac, char **av, t_data_philo *data)
{
	int	i;

	i = 0;
	init_data_philo(&data, ac, av);
	pthread_mutex_init(&data[0].all_data->mutex, NULL);
	pthread_mutex_init(&data[0].all_data->mutex_msg, NULL);
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
	pthread_mutex_destroy(&data[0].all_data->mutex_msg);
	free_all_data(data[0].all_data);
	free(data);
}

int	main(int ac, char **av)
{
	int				i;
	t_data_philo	data;

	i = 1;
	if (ac == 6 || ac == 5)
	{
		while (i < ac)
		{
			if (!check_valid_digit(i, av))
				return (1);
			i++;
		}
		master(ac, av, &data);
	}
	else
	{
		error();
		return (1);
	}
	return (0);
}
