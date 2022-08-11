/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:19:04 by jalamell          #+#    #+#             */
/*   Updated: 2022/08/11 16:12:15 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo.h"

typedef struct s_fork
{
	int				nb_philo;
	pthread_mutex_t	*forks;
}	t_fork;

static void	*fork_delete(t_fork *fork, int nb_to_delete)
{
	if (!fork)
		return (0);
	if (nb_to_delete >= 0 && fork->forks)
	{
		while (nb_to_delete--)
			pthread_mutex_destroy(fork->forks + nb_to_delete);
		free(fork->forks);
	}
	free(fork);
	return (0);
}

void	*ft_fork_init(int nb_philo)
{
	t_fork	*ret;
	int		i;

	ret = malloc(sizeof(t_fork));
	i = -1;
	if (!ret)
		return (0);
	ret->forks = malloc(nb_philo * sizeof(pthread_mutex_t));
	ret->nb_philo = nb_philo;
	if (!(ret->forks))
		return (fork_delete(ret, -1));
	while (++i < nb_philo)
		if (pthread_mutex_init((ret->forks) + i, 0))
			return (fork_delete(ret, i));
	return (ret);
}

void	ft_eat(t_philo *philo, volatile long *stop)
{
	t_fork *const			tfork = philo->data->fork;
	pthread_mutex_t			*m1;
	pthread_mutex_t			*m2;
	pthread_mutex_t *const	m3 = &philo->mutex;

	if (philo->id)
		m1 = tfork->forks + philo->id - 1;
	else
		m1 = tfork->forks + tfork->nb_philo - 1;
	m2 = m1;
	if ((philo->id) % 2)
		m2 = tfork->forks + philo->id;
	else
		m1 = tfork->forks + philo->id;
	pthread_mutex_lock(m1);
	ft_log(philo->id, 0);
	pthread_mutex_lock(m2);
	ft_log(philo->id, 0);
	pthread_mutex_lock(m3);
	philo->last_eat = ft_get_time(0);
	pthread_mutex_unlock(m3);
	ft_log(philo->id, 1);
	ft_usleep(philo->data->time_to_eat, stop);
	pthread_mutex_unlock(m1);
	pthread_mutex_unlock(m2);
}

void	*ft_fork_delete(void *fork)
{
	t_fork *const	tfork = fork;

	return (fork_delete(tfork, tfork->nb_philo));
}
