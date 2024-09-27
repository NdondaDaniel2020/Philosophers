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

void	*philo(void *arg_data)
{
	int		*id;
	t_data	*data;

	data = (t_data *)arg_data;
	id = malloc(sizeof(int));
	*id = data->id;
	while (1)
	{
		pthread_mutex_lock(&data->mutex);
		printf("Test %i\n", *id);
		pthread_mutex_unlock(&data->mutex);
	}
	return ((void *)"0");
}

void	master(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	init_data(data, ac, av);
	pthread_mutex_init(&data->mutex, NULL);
	while (i < data->number_of_philosophers)
	{
		data->id = i;
		pthread_create(&data->thread[i], NULL, philo, (void *)data);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->thread[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&data->mutex);
	free_data(data);
}

int	main(int ac, char **av)
{
	int		i;
	int		n;
	t_data	data;

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
			error(1, &data);
		master(ac, av, &data);
	}
	else
		error(1, &data);
}
