/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:53:07 by jalamell          #+#    #+#             */
/*   Updated: 2022/09/08 15:28:55 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo(void *arg)
{
	t_philo *const			p = arg;
	int						nb;

	if (p->id & 1)
		ft_usleep(5);
	nb = p->data->must_eat;
	while (1)
	{
		pthread_mutex_lock(&p->mutex);
		if (p->finish == -1)
		{
			pthread_mutex_unlock(&p->mutex);
			return (arg);
		}
		if (!(--nb))
			p->finish = 1;
		pthread_mutex_unlock(&p->mutex);
		ft_eat(p);
		ft_log(p->id, 3);
		ft_usleep(p->data->time_to_sleep);
	}
	return (arg);
}
