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

void	*philo_thread(void *arg_data)
{

	t_data_philo	*data;
	(void)arg_data;
	data = (t_data_philo *)arg_data;
	printf("Test %i\n", data->id);
	// while (1)
	// {
	// 	pthread_mutex_lock(&data->mutex);
	// 	printf("Test %i\n", *id);
	// 	pthread_mutex_unlock(&data->mutex);
	// }
	return ((void *)"0");
}

void	init_all_data_philo(t_all_data_philo *data, int ac, char **av)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(int) * data->number_of_philosophers);
	if (!data->fork)
		free_all_data(data);
	data->thread = malloc(sizeof(pthread_t) * data->number_of_philosophers);
	if (!data->thread)
		free_all_data(data);
	while (i < data->number_of_philosophers)
	{
		data->fork[i] = 0;
		i++;
	}
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->number_of_times_each_philosopher_must_eat = -1;
	if (ac == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
}

void init_data_philo(t_data_philo **data, int ac, char **av)
{
    int 				i;
    t_all_data_philo	*all_data;

    i = 0;
	all_data = malloc(sizeof(t_all_data_philo) * 1);
    init_all_data_philo(&all_data, ac, av);

    *data = malloc(sizeof(t_data_philo) * all_data.number_of_philosophers);
    while (i < all_data.number_of_philosophers)
    {
        (*data)[i].id = i + 1;
        (*data)[i].all_data = &all_data;
        i++;
    }
}

void	master(int ac, char **av, t_data_philo *data)
{
	int	i;

	i = 0;
	init_data_philo(&data, ac, av);
	// pthread_mutex_init(&data[0].all_data->mutex, NULL);

	// printf("[%i]\n", data[0].all_data->number_of_philosophers);
	
	while (i < data[0].all_data->number_of_philosophers)
	{
		printf("[%i] - ", i + 1);
		printf("[%i] + ", data[i].id);
		printf("[%li]\n", data[0].all_data->thread[i]);
		// pthread_create(&data[0].all_data->thread[i], NULL, philo_thread, (void *)&data[i]);
		i++;
	}
	// i = 0;
	// while (i < data[0].all_data->number_of_philosophers)
	// {
	// 	pthread_join(data[0].all_data->thread[i], NULL);
	// 	i++;
	// }
	// pthread_mutex_destroy(&data[0].all_data->mutex);
	// free_data(data);
}

int	main(int ac, char **av)
{
	int					i;
	int					n;
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
