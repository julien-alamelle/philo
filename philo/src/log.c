/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:56:42 by jalamell          #+#    #+#             */
/*   Updated: 2022/08/11 16:17:08 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

int	ft_get_time(int init);

typedef struct s_log_data
{
	volatile int	died;
	int				init;
	pthread_mutex_t	mutex;
}	t_log_data;

static t_log_data	*ft_get_log_data(int init)
{
	static t_log_data	data;

	if (init)
	{
		data.died = 0;
		init = 1;
		if (pthread_mutex_init(&data.mutex, 0))
			return (0);
	}
	return (&data);
}

int	ft_log_init(void)
{
	if (!ft_get_log_data(1))
		return (1);
	return (0);
}

/******************
 * log_type :     *
 * 0: took a fork *
 * 1: is eating   *
 * 2: is sleeping *
 * 3: is thinking *
 * 4: died        *
 ******************/

int	ft_log(int id, int log_type)
{
	t_log_data *const	data = ft_get_log_data(0);

	++id;
	pthread_mutex_lock(&(data->mutex));
	if (data->died)
	{
		pthread_mutex_unlock(&(data->mutex));
		return (1);
	}
	if (log_type == 0)
		printf("%d %d has taken a fork\n", ft_get_time(0), id);
	if (log_type == 1)
		printf("%d %d is eating\n", ft_get_time(0), id);
	if (log_type == 2)
		printf("%d %d is sleeping\n", ft_get_time(0), id);
	if (log_type == 3)
		printf("%d %d is thinking\n", ft_get_time(0), id);
	if (log_type == 4)
	{
		data->died = 1;
		printf("%d %d died\n", ft_get_time(0), id);
	}
	pthread_mutex_unlock(&(data->mutex));
	return (0);
}

void	ft_log_clear(void)
{
	t_log_data *const	data = ft_get_log_data(0);

	if (data->init)
		pthread_mutex_destroy(&(data->mutex));
	data->init = 0;
}
