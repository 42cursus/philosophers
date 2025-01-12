/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:29:54 by abelov            #+#    #+#             */
/*   Updated: 2025/01/12 13:30:06 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_status(t_philo *ph, char *status)
{
	pthread_mutex_lock(ph->stdout_lock);
	printf("%ld %d %s\n", ft_get_time() - ph->cookie->sim_start_time,
		   ph->id, status);
	pthread_mutex_unlock(ph->stdout_lock);
}

static int	take_forks(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->forks[left_hand]->fork_lock))
	{
		return (1);
	}
	ft_print_status(ph, FORK);
	if (pthread_mutex_lock(&ph->forks[right_hand]->fork_lock))
	{
		return (1);
	}
	ft_print_status(ph, FORK);
	return (0);
}

static int	put_forks(t_philo *ph)
{
	pthread_mutex_unlock(&ph->forks[left_hand]->fork_lock);
	pthread_mutex_unlock(&ph->forks[right_hand]->fork_lock);
	return (0);
}

static int	ft_sleep(t_philo *ph)
{
	int		to_sleep;

	ft_print_status(ph, SLEEP);
	to_sleep = ph->cookie->to_sleep;
	ft_usleep(to_sleep);
	return (1);
}

static int	ft_eat(t_philo *ph)
{
	int	to_eat;

	take_forks(ph);
	ph->last_meal_time = ft_get_time();
	ft_print_status(ph, EAT);
	to_eat = ph->cookie->to_eat;
	ft_usleep(to_eat);
	put_forks(ph);
	ph->times_eaten++;
	return (1);
}

void	*start_routine(void *philo)
{
	t_philo	*const	ph = philo;
	t_table *const	table = ph->cookie;

	while (!table->sim_start)
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


int ft_start_sim(t_table *table)
{
	int	i;

	table->sim_start_time = ft_get_time();
	i = -1;
	while (++i < table->num_of_philos)
	{
		table->phs[i].last_meal_time = table->sim_start_time;
		if (!table->max_eat_count)
			pthread_detach(table->phs[i].thread);
		else
			pthread_join(table->phs[i].thread, NULL);
	}
	table->sim_start = 1;
	while (!table->sim_end)
		usleep(10);
	return (0);
}
