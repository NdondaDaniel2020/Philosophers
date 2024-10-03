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

bool take_a_fork(t_data_philo *data)
{
	pthread_mutex_lock(&data->all_data->mutex);
	if (!data->all_data->fork[data->id]
		&& !data->all_data->fork[(data->id + 1)
			% data->all_data->number_of_philosophers])
	{	
		if (data->id == ((data->id + 1)
			% data->all_data->number_of_philosophers))
		{
			pthread_mutex_unlock(&data->all_data->mutex);
			return (false);
		}
		data->all_data->fork[(data->id + 1)
			% data->all_data->number_of_philosophers] = 1;	
		data->all_data->fork[data->id] = 1;
		pthread_mutex_unlock(&data->all_data->mutex);
		if (!data->all_data->monitor)
			printf("%ld %i has taken a fork\n",
				current_time(data->all_data->init_timeval), data->id + 1);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&data->all_data->mutex);
		return (false);
	}
}

void	is_eating(t_data_philo *data)
{
	if (data->all_data->number_of_times_each_philosopher_must_eat > 0)
	{
		pthread_mutex_lock(&data->all_data->mutex);
		data->all_data->number_of_times_each_philosopher_must_eat--;
		pthread_mutex_unlock(&data->all_data->mutex);
	}
	data->last_meal_time = current_time(data->all_data->init_timeval);
	if (!data->all_data->monitor)
		printf("%ld %i is eating\n",
			current_time(data->all_data->init_timeval), data->id + 1);
	usleep(data->all_data->time_to_eat * 1000);
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
	usleep(data->all_data->time_to_sleep * 1000);
}

void	*philo_thread(void *arg_data)
{
	bool			think;
	t_data_philo	*data;

	think = false;
	data = (t_data_philo *)arg_data;
	while (true)
	{
		data->time_without_eat = current_time(data->all_data->init_timeval) - data->last_meal_time;
        
		pthread_mutex_lock(&data->all_data->mutex);
		if ((data->time_without_eat - 1) > data->all_data->time_to_die)
        {
			printf("{time_without_eat [%ld] > time_to_die [%d]}\n", data->time_without_eat, data->all_data->time_to_die);
			printf("{time_without_eat [%ld] > time_to_die [%d]}\n", (data->time_without_eat - 1), data->all_data->time_to_die);
            if (!data->all_data->monitor)
            {
                printf("%ld %i died\n", current_time(data->all_data->init_timeval), data->id + 1);
                data->all_data->is_dead = true;
                data->all_data->monitor = true;
            }
        }
		pthread_mutex_unlock(&data->all_data->mutex);
		if (data->all_data->is_dead)
			return (NULL);
		if (take_a_fork(data))
		{
			think = false;
			is_eating(data);
			is_sleeping(data);
		}
		else if (!think)
		{
			think = true;
			printf("%ld %i is thinking\n", current_time(data->all_data->init_timeval), data->id + 1);
		}
	}
}

void	master(int ac, char **av, t_data_philo *data)
{
	int	i;

	i = 0;
	init_data_philo(&data, ac, av);
	pthread_mutex_init(&data[0].all_data->mutex, NULL);
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
	free_all_data(data[0].all_data);
	free(data);
}

int	main(int ac, char **av)
{
	int				i;
	int				n;
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
