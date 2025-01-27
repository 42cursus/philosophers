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

#include <sys/param.h>
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

static void	assign_forks(t_philo *ph, t_fork *forks, int pos)
{
	t_table *const	table = ph->table;

	if (ph->id % 2)
	{
		ph->forks[left_hand] = &forks[pos];
		ph->forks[right_hand] = &forks[(pos + 1) % table->n_of_philos];
	}
	else
	{
		ph->forks[left_hand] = &forks[(pos + 1) % table->n_of_philos];
		ph->forks[right_hand] = &forks[pos];
	}
}

static void	init_philos(t_table *table)
{
	int				i;
	static t_philo	philos[MAX_PHILOSOPHERS];
	t_philo			*philo;

	ft_memset(philos, 0, sizeof(t_philo) * MAX_PHILOSOPHERS);
	i = -1;
	while (++i < table->n_of_philos)
	{
		philo = &philos[i];
		philo->id = i + 1;
		philo->table = table;
		pthread_mutex_init(&philo->meal_mutex, NULL);
		assign_forks(philo, table->forks, i);
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
