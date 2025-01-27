/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 05:24:16 by abelov            #+#    #+#             */
/*   Updated: 2025/01/12 05:24:17 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_forks(t_table *table)
{
	static t_fork	forks[MAX_PHILOSOPHERS] = {0};
	int				i;

	memset(forks, 0, sizeof(t_fork) * MAX_PHILOSOPHERS);
	table->forks = forks;
	i = -1;
	while (++i < table->n_of_philos)
	{
		forks[i].id = i;
		pthread_mutex_init(&forks[i].mutex, NULL);
	}
}

static void	init_philos(t_table *table)
{
	static t_philo	philos[MAX_PHILOSOPHERS];
	int				i;
	t_philo			*philo;

	ft_memset(philos, 0, sizeof(t_philo) * table->n_of_philos);
	i = -1;
	while (++i < table->n_of_philos)
	{
		philo = &philos[i];
		philo->id = i;
		philo->table = table;
		pthread_mutex_init(&philo->last_meal_mutex, NULL);
		philo->forks[left_hand] = &table->forks[i];
		philo->forks[right_hand] = &table->forks[(i + 1) % table->n_of_philos];
	}
	table->phs = philos;
}

void	init_threads(t_table *table)
{
	int		i;
	t_philo	*ph;

	if (pthread_create(&table->monitor_thread, NULL,
			ft_monitor, table) != 0)
		exit((ft_perror(ERR_PTHREAD, NULL), -1));
	i = -1;
	while (++i < table->n_of_philos)
	{
		ph = &table->phs[i];
		if (pthread_create(&ph->thread, NULL,
				start_routine, ph))
			exit((ft_perror(ERR_PTHREAD, NULL), -1));
	}
}

void	init(t_table *table)
{
	init_forks(table);
	init_philos(table);
	pthread_mutex_init(&table->stdout_lock, NULL);
	pthread_mutex_init(&table->sim_mutex, NULL);
	pthread_mutex_lock(&table->sim_mutex);
	init_threads(table);
}
