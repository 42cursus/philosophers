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

int	has_everyone_ate(t_table *table)
{
	int						i;
	t_philo					*ph;
	register const u_int	max_eat_count = table->max_eat_count;
	register const int		num_of_philos = table->n_of_philos;

	if (max_eat_count)
	{
		i = -1;
		while (++i < num_of_philos)
		{
			ph = &table->phs[i];
			if ((ph->times_eaten < max_eat_count))
				break ;
		}
		if (i == num_of_philos)
		{
			table->sim_end = 1;
			return (-1);
		}
	}
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_table *const	table = arg;
	int				i;
	t_philo			*ph;

	while (!table->sim_start)
		ft_usleep(2);
	while (!has_everyone_ate(table) && !table->sim_end)
	{
		i = -1;
		while (++i < table->n_of_philos)
		{
			ph = &table->phs[i];
			if (((ft_get_time() - ph->last_meal_time) >= ph->cookie->to_live))
			{
				table->sim_end = 1;
				ft_print_status(ph, DIE);
				return (NULL);
			}
		}
	}
	return (NULL);
}
