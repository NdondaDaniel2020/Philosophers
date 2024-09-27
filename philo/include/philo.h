/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:10:13 by nmatondo          #+#    #+#             */
/*   Updated: 2024/09/23 11:10:20 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

typedef struct s_data
{
	int				id;
	pthread_t		*thread;
	pthread_mutex_t	mutex;
	int				*fork;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}					t_data;

void	free_data(t_data *data);
void	error(int i, t_data *data);
void	init_data(t_data *data, int ac, char **av);

int		str_isdigit(char *str);
int		ft_atoi(const char *nptr);

#endif