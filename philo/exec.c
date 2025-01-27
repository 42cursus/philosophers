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

static int	take_forks(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->forks[left_hand]->mutex))
		return (-1);
	ft_print_status(ph, FORK);
	if (ph->table->n_of_philos == 1)
		return ((void) pthread_mutex_unlock(&ph->forks[left_hand]->mutex), -1);
	if (pthread_mutex_lock(&ph->forks[right_hand]->mutex))
		return ((void) pthread_mutex_unlock(&ph->forks[left_hand]->mutex), -1);
	ft_print_status(ph, FORK);
	return (0);
}

__always_inline
static int	put_forks(t_philo *ph)
{
	pthread_mutex_unlock(&ph->forks[right_hand]->mutex);
	pthread_mutex_unlock(&ph->forks[left_hand]->mutex);
	return (0);
}

__always_inline
int	ft_sleep(t_philo *ph)
{
	ft_print_status(ph, SLEEP);
	ft_usleep(ph->table->to_sleep);
	return (1);
}

__always_inline
int	ft_update_meal_time(t_philo *ph)
{
	pthread_mutex_lock(&ph->meal_mutex);
	ph->last_meal_time = ft_get_time();
	ph->times_eaten++;
	pthread_mutex_unlock(&ph->meal_mutex);
	return (0);
}

int	ft_eat(t_philo *ph)
{
	if (!take_forks(ph))
	{
		if (sim_is_active(ph->table))
		{
			ft_update_meal_time(ph);
			ft_print_status(ph, EAT);
			ft_usleep(ph->table->to_eat);
		}
		put_forks(ph);
	}
	else
		return (-1);
	return (0);
}
