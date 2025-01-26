/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:30:40 by abelov            #+#    #+#             */
/*   Updated: 2025/01/12 22:30:40 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_has_eaten(t_philo *ph, const u_int max_eat_count)
{
	int	has_eaten;

	pthread_mutex_lock(&ph->last_meal_mutex);
	has_eaten = ph->times_eaten >= max_eat_count;
	pthread_mutex_unlock(&ph->last_meal_mutex);
	return (has_eaten);
}

int	has_everyone_ate(t_table *table)
{
	int						i;
	register const u_int	max_eat_count = table->max_eat_count;
	register const int		num_of_philos = table->n_of_philos;

	if (max_eat_count)
	{
		i = -1;
		while (++i < num_of_philos)
			if (!ft_has_eaten(&table->phs[i], max_eat_count))
				break;
		if (i == num_of_philos)
			return (set_sim_end(table), -1);
	}
	return (0);
}

int	ft_is_dead(t_philo *ph)
{
	int	ret;

	pthread_mutex_lock(&ph->last_meal_mutex);
	ret = (ft_get_time() - ph->last_meal_time) >= ph->table->to_live;
	pthread_mutex_unlock(&ph->last_meal_mutex);
	return (ret);
}

void set_sim_end(t_table *t)
{
	pthread_mutex_lock(&t->sim_mutex);
	t->sim_end = 1;
	pthread_mutex_unlock(&t->sim_mutex);
}

int sim_is_active(t_table *t)
{
	int								ret;

	pthread_mutex_lock(&t->sim_mutex);
	ret = t->sim_end == 0;
	pthread_mutex_unlock(&t->sim_mutex);
	return (ret);
}

void	*ft_monitor(void *arg)
{
	int						i;
	t_table *const			table = arg;
	t_philo					*ph;
	pthread_mutex_t *const	sim_mutex = &table->sim_mutex;

	pthread_mutex_lock(sim_mutex);
	pthread_mutex_unlock(sim_mutex);
	while (!has_everyone_ate(table) && sim_is_active(table))
	{
		i = -1;
		while (++i < table->n_of_philos)
		{
			ph = &table->phs[i];
			if (ft_is_dead(ph))
			{
				set_sim_end(table);
				ft_print_status(ph, PASSED);
				return (NULL);
			}
		}
	}
	return (NULL);
}
