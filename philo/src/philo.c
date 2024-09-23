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

void	master(int number_of_philosophers, int time_to_die, int time_to_eat,
	int time_to_sleep, int number_of_times_each_philosopher_must_eat)
{
	printf("[num %i], [die %i] [eat %i] [sleep %i] [each philoso %i]\n",
	number_of_philosophers, time_to_die, time_to_eat, 
		time_to_sleep, number_of_times_each_philosopher_must_eat);
}

// number_of_philosophers, time_to_die, time_to_eat,
// time_to_sleep, [number_of_times_each_philosopher_must_eat]

int	main(int ac, char **av)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	if (ac == 4 || ac == 5)
	{
		while (n)
			n = str_isdigit(av[i]);
		if (n == 0)
			error();
		if (ac == 4)
		{
			master(ft_atoi(av[1]), ft_atoi(av[2]),
				ft_atoi(av[3]), ft_atoi(av[4]), -1);
		}
		else
		{
			master(ft_atoi(av[1]), ft_atoi(av[2]),
				ft_atoi(av[3]), ft_atoi(av[4]), ft_atoi(av[5]));
		}
	}
	else
		error();
}
