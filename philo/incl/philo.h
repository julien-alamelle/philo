#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>

typedef struct timeval t_time;

typedef struct s_data
{
	int		nb_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat;
	t_time	time_start;
}	t_data;

#endif
