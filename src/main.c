/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:27:13 by abelov            #+#    #+#             */
/*   Updated: 2024/09/13 18:27:13 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
#include "philo.h"

/**
 * input validation INT_MAX
 * ./philo <Philo_No> <TTL> <TTE> <TTS> [times_to_eat]
 * could be only one philo
 * events with timestamps
 * TTL counts from start eating
 * philo can die during eating
 * we only count edgecase withing eating phase
 */
int	main(int argc, char **argv)
{
	t_table	*const table = &(t_table){0};

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo <number_of_philosophers> "
			"<time_to_die> <time_to_eat> <time_to_sleep> "
			"[number_of_times_each_philosopher_must_eat]\n");
		exit(EX_DATAERR);
	}
	if (parse(argc, argv, table) != 0)
		return (EX_DATAERR);
	init(table);
	ft_start_sim(table);
	return (EX_OK);
}
