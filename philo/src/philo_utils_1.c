/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:10:02 by nmatondo          #+#    #+#             */
/*   Updated: 2024/09/23 11:10:05 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(void)
{
	write(2, "ERROR\n", 6);
	write(2, "<number_of_philosophers> <time_to_die> <time_to_eat> ", 53);
	write(2, "<time_to_sleep> <number_of_times_each_philosopher_must_eat>", 59);
}

long	current_time(struct timeval init_tv)
{
	long			re;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	re = ((tv.tv_sec - init_tv.tv_sec) * 1000)
		+ ((tv.tv_usec - init_tv.tv_usec) / 1000);
	return (re);
	
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
