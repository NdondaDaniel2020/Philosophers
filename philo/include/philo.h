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
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

typedef struct s_all_data_philo
{
	int				id;
	pthread_t		*thread;
	pthread_mutex_t	mutex;
	int				*fork;
	bool			is_dead;
	bool			monitor;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				number_of_times_philosophers_should_eat;
	struct timeval	init_timeval;
}					t_all_data_philo;

typedef struct s_data_philo
{
	int					id;
	t_all_data_philo	*all_data;
	long				time_without_eat;
	long				last_meal_time;
	bool				have_a_fork;
}						t_data_philo;


void	*philo_thread(void *arg_data);
void	is_eating(t_data_philo *data);
void	is_sleeping(t_data_philo *data);

void	free_all_data(t_all_data_philo *data);
void	init_data_philo(t_data_philo **data, int ac, char **av);
void	init_all_data_philo(t_all_data_philo *data, int ac, char **av);

void	error(void);
int		str_isdigit(char *str);
int		ft_atoi(const char *nptr);
long	current_time(struct timeval init_tv);

#endif