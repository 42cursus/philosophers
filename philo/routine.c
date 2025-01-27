/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:32:04 by abelov            #+#    #+#             */
/*   Updated: 2025/01/26 12:42:36 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_routine(void *philo)
{
	t_philo *const			ph = philo;
	t_table *const			table = ph->table;

	pthread_mutex_lock(&table->sim_mutex);
	pthread_mutex_unlock(&table->sim_mutex);
	while (sim_is_active(table))
	{
		ft_print_status(ph, THINK);
		if (ph->id % 2)
			ft_usleep(1);
		if (ft_eat(ph))
			break ;
		if (sim_is_active(table))
			ft_sleep(ph);
	}
	return (NULL);
}

void	ft_destroy(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_of_philos)
		pthread_mutex_destroy(&table->forks[i].mutex);
	i = -1;
	while (++i < table->n_of_philos)
		pthread_mutex_destroy(&table->phs[i].meal_mutex);
	pthread_mutex_destroy(&table->sim_mutex);
}

int	ft_start_sim(t_table *table)
{
	int				i;
	const u_long	start_time = ft_get_time();

	i = -1;
	while (++i < table->n_of_philos)
	{
		table->phs[i].sim_start_time = start_time;
		table->phs[i].last_meal_time = start_time;
	}
	table->sim_start_time = start_time;
	pthread_mutex_unlock(&table->sim_mutex);
	i = -1;
	while (++i < table->n_of_philos)
		pthread_join(table->phs[i].thread, NULL);
	pthread_join(table->monitor_thread, NULL);
	ft_destroy(table);
	return (0);
}
