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
	int	ret;

	ret = 0;
	pthread_mutex_lock(&ph->times_eaten_mutex);
	if (max_eat_count && ph->times_eaten >= max_eat_count)
		ret = 1;
	pthread_mutex_unlock(&ph->times_eaten_mutex);
	return (ret);
}

void	has_everyone_ate(t_table *table)
{
	int						i;
	int						number_of_people_who_ate;
	t_philo					*ph;
	register const u_int	max_eat_count = table->max_eat_count;
	register const int		num_of_philos = table->num_of_philos;

	if (max_eat_count)
	{
		number_of_people_who_ate = 0;
		i = -1;
		while (++i < num_of_philos)
		{
			ph = &table->phs[i];
			if (ft_has_eaten(ph, max_eat_count))
				number_of_people_who_ate++;
		}
		if (number_of_people_who_ate == num_of_philos)
		{
			table->sim_end = 1;
			ph = &(t_philo){.cookie = table, .id = -1};
			ft_print_status(ph, ISFULL);
		}
	}
}

int	ft_is_dead(t_philo *ph)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&ph->last_meal_mutex);
	if ((ft_get_time() - ph->last_meal_time) >= ph->cookie->to_live)
	{
		pthread_mutex_unlock(&ph->last_meal_mutex);
		ret = 1;
	}
	else
		pthread_mutex_unlock(&ph->last_meal_mutex);
	return (ret);
}

void	*ft_monitor(void *arg)
{
	t_table *const	table = arg;
	int				i;
	t_philo			*ph;

	while (!table->sim_start)
		ft_usleep(20);
	while (!table->sim_end)
	{
		i = -1;
		while (++i < table->num_of_philos && !table->sim_end)
		{
			ph = &table->phs[i];
			if (ft_is_dead(ph))
			{
				table->sim_end = 1;
				ft_print_status(ph, PASSED);
			}
		}
		if (!table->sim_end)
			has_everyone_ate(table);
	}
	return (NULL);
}
