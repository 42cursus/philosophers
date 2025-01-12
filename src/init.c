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
	static t_fork	forks[MAX_PHILOSOPHERS];
	int				i;

	memset(forks, 0, sizeof(t_fork));
	table->forks = forks;

	if (table->num_of_philos == 1)
		table->num_of_forks = 2;
	i = -1;
	while (++i < table->num_of_forks)
	{
		table->forks[i].id = i;
		pthread_mutex_init(&table->forks[i].fork_lock, NULL);
	}
}

static void	init_philos(t_table *table)
{
	static t_philo	philos[MAX_PHILOSOPHERS];
	int				i;
	t_philo			*philo;

	memset(philos, 0, sizeof(t_philo) * table->num_of_philos);

	i = -1;
	while (++i < table->num_of_philos)
	{
		philo = &philos[i];
		philo->id = i;
		philo->cookie = table;
		philo->stdout_lock = &table->stdout_lock;
		philo->forks[left_hand] = &table->forks[i];
		philo->forks[right_hand] = &table->forks[(i + 1) % table->num_of_forks];
	}
	table->phs = philos;
}

void init_threads(t_table *table)
{
	int				i;

	i = -1;
	while (++i < table->num_of_philos)
	{
		if (pthread_create(&table->phs[i].thread, NULL,
						   start_routine, &table->phs[i]))
			exit((ft_perror(ERR_PTHREAD, NULL), -1));
	}
	if (pthread_create(&table->monitor_thread, NULL,
					   ft_monitor, table) != 0)
		exit((ft_perror(ERR_PTHREAD, NULL), -1));
}

void	init(t_table *table)
{
	init_forks(table);
	init_philos(table);
	pthread_mutex_init(&table->stdout_lock, NULL);
	init_threads(table);
}
