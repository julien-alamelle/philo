/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:53:07 by jalamell          #+#    #+#             */
/*   Updated: 2022/08/11 16:54:14 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo(void *arg)
{
	t_philo *const			p = arg;
	int						nb;
	volatile long *const	stop = &(p->data->nb_philo);

	nb = p->data->must_eat;
	while (*stop)
	{
		ft_eat(p, stop);
		if (*stop)
			ft_log(p->id, 3);
		if (!(--nb))
			p->finish = 1;
		ft_usleep(p->data->time_to_sleep, stop);
	}
	return (arg);
}
