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
		"died"
	};

	pthread_mutex_lock(&ph->table->stdout_lock);
	if (sim_is_active(ph->table) || status_code == PASSED)
	{
		printf("%ld %d %s\n", ft_get_time() - ph->sim_start_time,
			ph->id, statuses[status_code]);
	}
	pthread_mutex_unlock(&ph->table->stdout_lock);
}

void	ft_perror(const char *msg, const char *end)
{
	if (!end)
		end = "\n";
	printf("%s%s", msg, end);
}
