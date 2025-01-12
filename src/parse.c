/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 03:48:56 by abelov            #+#    #+#             */
/*   Updated: 2025/01/12 03:48:56 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_val(t_table *info, u_long val, int argc)
{
	char errbuf[1024];

	if (val == 0 || !((int)val > INT_MIN && (int)val < INT_MAX))
		exit((ft_perror(ERR_INPUT, NULL), -1));
	if (argc == num_of_philos)
	{
		if (val > MAX_PHILOSOPHERS)
		{
			ft_uitoa_buf(MAX_PHILOSOPHERS, errbuf, 1024);
			errbuf[ft_strlen(errbuf)] = '\n';
			errbuf[ft_strlen(errbuf) + 1] = '\0';
			exit((ft_perror(ERR_MAXPHILO, errbuf), -1));
		}
		info->num_of_philos = val;
		info->num_of_forks = val;
	}
	else if (argc == time_to_die)
		info->to_live = val;
	else if (argc == time_to_eat)
		info->to_eat = val;
	else if (argc == time_to_sleep)
		info->to_sleep = val;
	else if (argc == max_eat_count)
		info->max_eat_count = val;
}

int	parse(int argc, char **argv, t_table *table)
{
	char				*endptr;
	u_long				val;
	int					i;
	const char *const	lt[PARAM_COUNT] = {
		"number_of_philosophers",
		"time_to_die",
		"time_to_eat",
		"time_to_sleep",
		"number_of_times_each_philosopher_must_eat",
	};

	i = 0;
	while (++i < argc)
	{
		endptr = NULL;
		errno = 0;
		val = (int)ft_strtoul(argv[i], &endptr, 10);
		if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
			|| (errno != 0 && val == 0) || (endptr && *endptr))
		{
			printf("error parsing param \"%s\"\n", lt[i - 1]);
			return (-1);
		}
		assign_val(table, val, i);
	}
	return (0);
}
