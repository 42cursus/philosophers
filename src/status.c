/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:33:06 by abelov            #+#    #+#             */
/*   Updated: 2025/01/25 15:33:06 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_status(t_philo *ph, unsigned char status_code)
{
	static const char	*statuses[6] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"has passed away",
		"everyone ate"
	};

	pthread_mutex_lock(&ph->cookie->stdout_lock);
	if (ph->id == -1 && status_code == ISFULL)
		printf("%ld %s\n", ft_get_time() - ph->cookie->sim_start_time,
			   statuses[status_code]);
	else if (!ph->cookie->sim_end || status_code == PASSED)
		printf("%ld %d %s\n", ft_get_time() - ph->cookie->sim_start_time,
			   ph->id, statuses[status_code]);
	pthread_mutex_unlock(&ph->cookie->stdout_lock);
}
