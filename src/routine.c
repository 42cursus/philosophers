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
		ft_usleep(20);
	if (ph->id == 0)
		ft_usleep(20);
	while (!table->sim_end)
	{
		if (!table->sim_end)
			ft_print_status(ph, THINK);
		if (!table->sim_end)
			ft_eat(ph);
		if (!table->sim_end)
			ft_sleep(ph);
	}
	return (NULL);
}

void	ft_destroy(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_forks)
		pthread_mutex_destroy(&table->forks[i].mutex);
	i = -1;
	while (++i < table->num_of_philos)
	{
		pthread_mutex_destroy(&table->phs[i].times_eaten_mutex);
		pthread_mutex_destroy(&table->phs[i].last_meal_mutex);
	}
}

int	ft_start_sim(t_table *table)
{
	int	i;

	table->sim_start_time = ft_get_time();
	i = -1;
	while (++i < table->num_of_philos)
		table->phs[i].last_meal_time = table->sim_start_time;
	table->sim_start = 1;
	i = -1;
	while (++i < table->num_of_philos)
		pthread_join(table->phs[i].thread, NULL);
	while (!table->sim_end)
		usleep(10);
	pthread_join(table->monitor_thread, NULL);
	ft_destroy(table);
	return (0);
}

