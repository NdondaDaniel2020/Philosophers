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

long	current_time(struct timeval init_tv)
{
	long			re;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	re = ((tv.tv_sec - init_tv.tv_sec) * 1000)
		+ ((tv.tv_usec - init_tv.tv_usec) / 1000);
	return (re);
}

int	main(void)
{
	long			re;
	struct timeval	init_tv;

	gettimeofday(&init_tv, NULL);
	while (true)
	{
		printf("%ld\n", current_time(init_tv));
	}
	return (0);
}
