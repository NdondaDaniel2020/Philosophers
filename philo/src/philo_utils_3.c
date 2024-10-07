/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:10:02 by nmatondo          #+#    #+#             */
/*   Updated: 2024/09/23 11:10:05 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_eating(t_data_philo *data)
{
	data->have_a_fork = false;
	data->last_meal_time = current_time(data->all_data->init_timeval);
	if (data->all_data->number_of_times_each_philosopher_must_eat > 0)
	{
		pthread_mutex_lock(&data->all_data->mutex);
		data->all_data->number_of_times_each_philosopher_must_eat--;
		pthread_mutex_unlock(&data->all_data->mutex);
	}
	if (!data->all_data->monitor)
		printf("%ld %i is eating\n",
			current_time(data->all_data->init_timeval), data->id + 1);
	usleep(data->all_data->time_to_eat);
	pthread_mutex_lock(&data->all_data->mutex);
	data->all_data->fork[data->id] = 0;
	data->all_data->fork[(data->id + 1) % data->all_data->number_of_philosophers] = 0;
	pthread_mutex_unlock(&data->all_data->mutex);
	if (data->all_data->number_of_times_each_philosopher_must_eat == 0)
		data->all_data->is_dead = true;
}

void	is_sleeping(t_data_philo *data)
{
	if (!data->all_data->monitor)
		printf("%ld %i is sleeping\n",
			current_time(data->all_data->init_timeval), data->id + 1);
	usleep(data->all_data->time_to_sleep);
}
