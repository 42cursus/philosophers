typedef enum	e_state
{
	ithink,
	ieat,
	isleep
}	t_state;

typedef struct s_philosopher {
	int             id;
	int             last_meal_time;
	int             times_eaten;
	pthread_t       thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
}	t_philosopher;

typedef struct s_table {
	int             number_of_philosophers;
	int             time_to_die;
	int             time_to_eat;
	int             time_to_sleep;
	pthread_mutex_t *forks;
	t_philosopher   *philosophers;
}	t_table;


void init_table(t_table *table)
{
	table->number_of_philosophers = n_philosophers;
	table->time_to_die = time_to_die;
	table->time_to_eat = time_to_eat;
	table->time_to_sleep = time_to_sleep;

	// Allocate memory for forks and philosophers
	table->forks = malloc(sizeof(pthread_mutex_t) * n_philosophers);
	table->philosophers = malloc(sizeof(t_philosopher) * n_philosophers);

	// Initialize forks (mutexes)
	for (int i = 0; i < n_philosophers; i++) {
		pthread_mutex_init(&table->forks[i], NULL);
	}

	// Initialize philosophers
	for (int i = 0; i < n_philosophers; i++) {
		table->philosophers[i].id = i + 1;
		table->philosophers[i].last_meal_time = 0;
		table->philosophers[i].times_eaten = 0;
		table->philosophers[i].left_fork = &table->forks[i];
		table->philosophers[i].right_fork = &table->forks[(i + 1) % n_philosophers]; // Wrap around
	}
}


int	main(int argc, char **argv)
{
	t_table table;

	table->number_of_philosophers = n_philosophers;
	table->time_to_die = time_to_die;
	table->time_to_eat = time_to_eat;
	table->time_to_sleep = time_to_sleep;

	if (argc != 1)
		if (argv != NULL && *argv != NULL)
			ft_printf("%s\n", *argv);
	return (0);
}
