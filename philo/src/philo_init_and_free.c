/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_and_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:10:02 by nmatondo          #+#    #+#             */
/*   Updated: 2024/09/23 11:10:05 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_all_data_philo(t_all_data_philo *data, int ac, char **av)
{
	gettimeofday(&data->init_timeval, NULL);
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]) * 1000;
	data->is_dead = false;
	data->monitor = false;
	data->time_to_sleep = ft_atoi(av[4]) * 1000;
	data->number_of_times_each_philosopher_must_eat = -1;
	if (ac == 6)
	{
		data->number_of_times_each_philosopher_must_eat = \
		(ft_atoi(av[5]) * ft_atoi(av[1]));
	}
	data->fork = malloc(sizeof(int) * data->number_of_philosophers);
	if (!data->fork)
		return ;
	data->thread = malloc(sizeof(pthread_t) * data->number_of_philosophers);
	if (!data->thread)
	{
		free_all_data(data);
		return ;
	}
}

void	init_data_philo(t_data_philo **data, int ac, char **av)
{
	int					i;
	t_all_data_philo	*all_data;

	i = 0;
	all_data = malloc(sizeof(t_all_data_philo) * 1);
	init_all_data_philo(all_data, ac, av);
	*data = malloc(sizeof(t_data_philo) * all_data->number_of_philosophers);
	while (i < all_data->number_of_philosophers)
	{
		(*data)[i].id = i;
		(*data)[i].have_a_fork = false;
		(*data)[i].all_data = all_data;
		i++;
	}
	i = 0;
	while (i < all_data->number_of_philosophers)
	{
		all_data->fork[i] = 0;
		i++;
	}
}

void	free_all_data(t_all_data_philo *data)
{
	if (data->fork)
		free(data->fork);
	if (data->thread)
		free(data->thread);
	if (data)
		free(data);
}
