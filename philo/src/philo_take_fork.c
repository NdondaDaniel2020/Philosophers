/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_take_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:10:02 by nmatondo          #+#    #+#             */
/*   Updated: 2024/09/23 11:10:05 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	take_a_left_fork(t_data_philo *data)
{
	pthread_mutex_lock(&data->all_data->mutex);
	if (!data->all_data->fork[data->id])
	{
		data->all_data->fork[data->id] = 1;
		if (!data->all_data->monitor)
			print_menssage(data, "has taken a fork");
		pthread_mutex_unlock(&data->all_data->mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->all_data->mutex);
	return (false);
}

static bool	take_a_right_fork(t_data_philo *data)
{
	pthread_mutex_lock(&data->all_data->mutex);
	if (!data->all_data->fork[(data->id + 1)
			% data->all_data->number_of_philosophers])
	{
		data->all_data->fork[(data->id + 1)
			% data->all_data->number_of_philosophers] = 1;
		if (!data->all_data->monitor)
			print_menssage(data, "has taken a fork");
		pthread_mutex_unlock(&data->all_data->mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->all_data->mutex);
	return (false);
}

static bool	even_philosofer(t_data_philo *data)
{
	bool	left;
	bool	right;

	left = false;
	right = false;
	right = take_a_right_fork(data);
	if (right)
	{
		left = take_a_left_fork(data);
		if (left)
			return (true);
		data->have_a_fork = true;
	}
	if (!right && data->have_a_fork)
	{
		left = take_a_left_fork(data);
		if (left)
			return (true);
	}
	return (false);
}

static bool	odd_philosofer(t_data_philo *data)
{
	bool	left;
	bool	right;

	left = false;
	right = false;
	left = take_a_left_fork(data);
	if (left)
	{
		right = take_a_right_fork(data);
		if (right)
			return (true);
		data->have_a_fork = true;
	}
	if (!left && data->have_a_fork)
	{
		right = take_a_right_fork(data);
		if (right)
			return (true);
	}
	return (false);
}

bool	take_a_fork(t_data_philo *data)
{
	if ((data->id + 1) % 2 == 0)
		return (even_philosofer(data));
	else
		return (odd_philosofer(data));
}
