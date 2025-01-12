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

void	has_everyone_ate(t_table *table)
{
	int		i;
	int		number_of_people_who_ate;

	number_of_people_who_ate = 0;
	i = -1;
	while (i < table->num_of_philos && table->max_eat_count)
		if (table->phs[i].times_eaten == table->max_eat_count)
			number_of_people_who_ate++;
	if (i == number_of_people_who_ate)
		table->sim_end = 1;
}

void	*ft_monitor(void *arg)
{
	t_table *const table = arg;
	t_philo	*ph;
	int		i;

	while (!table->sim_start)
		ft_usleep(20);
	while(!table->sim_end)
	{
		i = -1;
		while(++i < table->num_of_philos && !table->sim_end)
		{
			ph = &table->phs[i];
			if ((ft_get_time() - ph->last_meal_time) >= table->to_live)
				table->sim_end = (ft_print_status(ph, PASSED), 1);
		}
		has_everyone_ate(table);
	}
	return (NULL);
}
