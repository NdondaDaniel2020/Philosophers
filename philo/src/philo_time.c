/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:10:02 by nmatondo          #+#    #+#             */
/*   Updated: 2024/09/23 11:10:05 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	current_time(struct timeval init_tv)
{
	long			re;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	re = ((tv.tv_sec - init_tv.tv_sec) * 1000)
		+ ((tv.tv_usec - init_tv.tv_usec) / 1000);
	return (re);
}

void	print_menssage(t_data_philo *data, char *mensage)
{
	pthread_mutex_lock(&data->all_data->mutex_msg);
	printf("%ld %i %s\n", current_time(data->all_data->init_timeval),
		data->id + 1, mensage);
	pthread_mutex_unlock(&data->all_data->mutex_msg);
}
