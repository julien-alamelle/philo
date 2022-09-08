/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:49:07 by jalamell          #+#    #+#             */
/*   Updated: 2022/09/08 14:23:15 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_data
{
	volatile long	nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat;
	void			*fork;
}	t_data;

typedef struct s_philo
{
	volatile long	last_eat;
	volatile long	finish;
	long			id;
	t_data			*data;
	pthread_t		philo;
	pthread_mutex_t	mutex;
}	t_philo;

void	*ft_fork_init(int nb_philo);
void	ft_eat(t_philo *philo);
void	*ft_fork_delete(void *fork);

int		ft_log_init(void);
int		ft_log(int id, int log_type);
void	ft_log_clear(void);

int		ft_get_time(int init);
void	ft_usleep(int time);

void	*ft_calloc(int nb_block, int size_blocks);
int		ft_atoi(char *str);

void	*ft_philo(void *arg);

#endif
