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
	int	hands[2];

	if (ph->id % 2)
	{
		hands[0] = left_hand;
		hands[1] = right_hand;
	}
	else
	{
		hands[0] = right_hand;
		hands[1] = left_hand;
	}
	if (pthread_mutex_lock(&ph->forks[hands[0]]->mutex))
		return (1);
	ft_print_status(ph, FORK);
	if (pthread_mutex_lock(&ph->forks[hands[1]]->mutex))
		return (1);
	ft_print_status(ph, FORK);
	return (0);
}

static int	put_forks(t_philo *ph)
{
	pthread_mutex_unlock(&ph->forks[left_hand]->mutex);
	pthread_mutex_unlock(&ph->forks[right_hand]->mutex);
	return (0);
}


int	ft_sleep(t_philo *ph)
{
	ft_print_status(ph, SLEEP);
	ft_usleep(ph->cookie->to_sleep);
	return (1);
}

void	ft_update_last_meal_time(t_philo *ph)
{
	pthread_mutex_lock(&ph->last_meal_mutex);
	ph->last_meal_time = ft_get_time();
	pthread_mutex_unlock(&ph->last_meal_mutex);
}

int	ft_eat(t_philo *ph)
{
	if (!take_forks(ph))
	{
		ft_update_last_meal_time(ph);
		ft_print_status(ph, EAT);
		ft_usleep(ph->cookie->to_eat);
		put_forks(ph);
		pthread_mutex_lock(&ph->times_eaten_mutex);
		ph->times_eaten++;
		pthread_mutex_unlock(&ph->times_eaten_mutex);
	}
	return (1);
}

