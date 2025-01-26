/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 06:18:56 by abelov            #+#    #+#             */
/*   Updated: 2025/01/12 06:18:57 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <sys/types.h>
#include "philo.h"

u_long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

u_long	ft_get_start_time(t_table  *table)
{
	u_long	start_time;

	pthread_mutex_lock(&table->sim_mutex);
	start_time = table->sim_start_time;
	pthread_mutex_unlock(&table->sim_mutex);
	return (start_time);
}

/**
 * https://blog.habets.se/2010/09/gettimeofday-should-never-be-used-to-measure-time.html
 */
void	ft_usleep(u_int64_t time)
{
	u_long	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < time)
		usleep(1000);
}
