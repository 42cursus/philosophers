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
#include "philo.h"

u_long	ft_get_time(void)
{
	struct timeval	current_time;
	long long int	time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long long int time)
{
	u_long	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < time)
		usleep(10);
}
