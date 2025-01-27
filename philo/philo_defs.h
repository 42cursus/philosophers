/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_defs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 04:17:57 by abelov            #+#    #+#             */
/*   Updated: 2025/01/25 22:26:04 by abelov           ###   ########.fr       */
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

typedef enum e_status
{
	FORK = 0,
	EAT,
	SLEEP,
	THINK,
	PASSED,
	ISFULL
}	t_status;

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

typedef volatile _Atomic int			t_atomic_int;
typedef volatile _Atomic unsigned int	t_atomic_u_int;
typedef volatile _Atomic unsigned long	t_atomic_u_long;
typedef struct s_fork
{
	int				id;
	int				taken;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_table
{
	u_long			sim_start_time;
	pthread_mutex_t	sim_mutex;
	t_atomic_int	sim_start;
	t_atomic_int	sim_end;
	u_long			to_live;
	u_long			to_eat;
	u_long			to_think;
	u_long			to_sleep;
	u_int			max_eat_count;
	pthread_mutex_t	stdout_lock;
	pthread_t		monitor_thread;
	t_fork			*forks;
	struct s_philo	*phs;
	int				n_of_philos;
}	t_table;

typedef struct s_philo
{
	int				id;
	u_long			last_meal_time;
	pthread_mutex_t	last_meal_mutex;
	u_int			times_eaten;
	u_long			sim_start_time;
	t_fork			*forks[2];
	pthread_t		thread;
	t_table			*table;
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
