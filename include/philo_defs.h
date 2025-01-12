/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_defs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 04:17:57 by abelov            #+#    #+#             */
/*   Updated: 2025/01/12 04:17:57 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_DEFS_H
# define PHILO_DEFS_H
# include <sys/types.h>
# include <limits.h>

# define PHILO_H
# define MAX_PHILOSOPHERS 1024
# define PARAM_COUNT 6

# define ERR_INPUT		"Invalid input."
# define ERR_ARG_COUNT	"Invalid number of arguments."
# define ERR_ARG_VALUE	"Invalid argument value."
# define ERR_PTHREAD	"Can't create thread."
# define ERR_MUTEX		"Can't mutex."
# define ERR_MAXPHILO	"We can only handle amount of philosophers up to: "

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define PASSED "has passed away"

typedef enum e_hand
{
	left_hand = 0,
	right_hand
}	t_hand;

typedef enum e_param
{
	num_of_philos = 1,
	time_to_die,
	time_to_eat,
	time_to_sleep,
	max_eat_count
}	t_param;

typedef volatile _Atomic int	t_atomic_int;
typedef struct s_fork
{
	int				id;
	pthread_mutex_t	fork_lock;
}	t_fork;

typedef struct s_table
{
	u_long			sim_start_time;
	t_atomic_int	sim_start;
	t_atomic_int	sim_end;
	int 			to_live;
	int 			to_eat;
	int 			to_sleep;
	int 			max_eat_count;
	pthread_mutex_t	stdout_lock;
	pthread_t		monitor_thread;
	t_fork			*forks;
	struct s_philo	*phs;
	u_int			num_of_philos;
	u_int			num_of_forks;
}	t_table;

typedef struct s_philo
{
	int				id;
	u_long			last_meal_time;
	u_int			times_eaten;
	t_fork			*forks[2];
	pthread_t		thread;
	t_table			*cookie;
	pthread_mutex_t	*stdout_lock;
}	t_philo;

typedef struct s_convert
{
	int				neg;
	int				any;
	unsigned long	acc;
	int				cutlim;
	unsigned long	cutoff;
}	t_conv;

#endif //PHILO_DEFS_H
