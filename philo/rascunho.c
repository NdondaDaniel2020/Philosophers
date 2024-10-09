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
