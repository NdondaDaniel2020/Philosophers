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

void	error(int i, t_data *data)
{
	write(2, "ERROR\n", 6);
	if (i == 1)
	{
		write(2, "<number_of_philosophers> <time_to_die> <time_to_eat> ", 53);
		write(2, "<time_to_sleep> <number_of_times_each_philosopher_must_eat>", 59);
	}
	free_data(data);
	exit (1);
}

void	free_data(t_data *data)
{
	if (data->fork)
		free(data->fork);
	if (data->thread)
		free(data->thread);
}

void	init_data(t_data *data, int number_of_philosophers)
{
	int	i = 0;

	data->fork = malloc(sizeof(int) * number_of_philosophers);
	if (!data->fork)
		error(0, data);
	data->thread = malloc(sizeof(pthread_t) * number_of_philosophers);
	if (!data->thread)
		error(0, data);
	while (i < number_of_philosophers)
	{
		data->fork[i] = 0;
		i++;
	}
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	str_isdigit(char *str)
{
	int	i;

	i = 1;
	while (i && *str)
	{
		if (i == '+')
			i = 1;
		else
			i = ft_isdigit(*str);
		++str;
	}
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	s;
	int	r;

	i = 0;
	s = 1;
	r = 0;
	while ((nptr[i] >= '\a' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			s *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		r = (nptr[i] - '0') + (r * 10);
		i++;
	}
	return (r * s);
}
