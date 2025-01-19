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

void	ft_print_status(t_philo *ph, unsigned char status_code)
{
	static const char *statuses[6] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"has passed away",
		"everyone ate"
	};
	pthread_mutex_lock(&ph->cookie->stdout_lock);
	if (ph->id == -1 && status_code == ISFULL)
		printf("%ld %s\n", ft_get_time() - ph->cookie->sim_start_time,
			   statuses[status_code]);
	else if (!ph->cookie->sim_end || status_code == PASSED)
	{

		printf("%ld %d %s\n", ft_get_time() - ph->cookie->sim_start_time,
		   ph->id, statuses[status_code]);
	}
	pthread_mutex_unlock(&ph->cookie->stdout_lock);
}

static int	take_forks(t_philo *ph)
{
	int hands[2];

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

static int	ft_sleep(t_philo *ph)
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

static int	ft_eat(t_philo *ph)
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

void	*start_routine(void *philo)
{
	t_philo	*const	ph = philo;
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


int ft_start_sim(t_table *table)
{
	int	i;

	table->sim_start_time = ft_get_time();
	i = -1;
	while (++i < table->num_of_philos)
		table->phs[i].last_meal_time = table->sim_start_time;

	table->sim_start = 1;
	i = -1;
	while (++i < table->num_of_philos)
	{
//		if (!table->max_eat_count)
//			pthread_detach(table->phs[i].thread);
//		else
			pthread_join(table->phs[i].thread, NULL);
	}
	while (!table->sim_end)
		usleep(10);
	pthread_join(table->monitor_thread, NULL);
	ft_destroy(table);
	return (0);
}
