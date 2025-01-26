/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:32:04 by abelov            #+#    #+#             */
/*   Updated: 2025/01/25 15:32:05 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_routine(void *philo)
{
	t_philo *const	ph = philo;
	t_table *const	table = ph->cookie;

	while (!table->sim_start)
		usleep(2);
	while (!table->sim_end)
	{
		if (!table->sim_end)
			ft_print_status(ph, THINK);
		if (!table->sim_end)
		{
			if (ph->id % 2)
				ft_usleep(1);
			if (ft_eat(ph))
				break ;
		}
		if (!table->sim_end)
			ft_sleep(ph);
	}
	return (NULL);
}

int	ft_start_sim(t_table *table)
{
	int	i;

	table->sim_start_time = ft_get_time();
	i = -1;
	while (++i < table->n_of_philos)
		table->phs[i].last_meal_time = table->sim_start_time;
	table->sim_start = 1;
	i = -1;
	while (++i < table->n_of_philos)
		pthread_join(table->phs[i].thread, NULL);
	while (!table->sim_end)
		usleep(10);
	pthread_join(table->monitor_thread, NULL);
	i = -1;
	while (++i < table->n_of_philos)
		pthread_mutex_destroy(&table->forks[i].mutex);
	return (0);
}
