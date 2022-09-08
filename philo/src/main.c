/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:19:35 by jalamell          #+#    #+#             */
/*   Updated: 2022/09/08 16:02:45 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "philo.h"

static int	data_init(t_data *data, int ac, char **av)
{
	if (ac < 4 || ac > 5)
		return (write(2, "Error: Require 4 or 5 arguments\n", 32));
	data->nb_philo = ft_atoi(av[0]);
	data->time_to_die = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[3]);
	data->must_eat = ft_atoi(av[4]);
	if (data->nb_philo < 1 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->must_eat < 0)
		return (write(2, "Error: Bad arguments\n", 21));
	if (ac == 5 && data->must_eat <= 0)
		return (1);
	if (data->nb_philo == 1)
		return (printf("0 1 has taken a fork\n%ld 1 died\n",
				data->time_to_die));
	ft_log_init();
	data->fork = ft_fork_init(data->nb_philo);
	return (0);
}

static int	ft_exit(t_data *data, t_philo *tab)
{
	int	i;

	if (tab)
	{
		i = -1;
		while (tab[++i].philo)
		{
			pthread_mutex_lock(&tab[i].mutex);
			tab[i].finish = -1;
			pthread_mutex_unlock(&tab[i].mutex);
		}
		i = -1;
		while (tab[++i].philo)
		{
			pthread_join(tab[i].philo, 0);
			pthread_mutex_destroy(&tab[i].mutex);
		}
		free(tab);
	}
	data->fork = ft_fork_delete(data->fork);
	ft_log_clear();
	return (0);
}

static void	philo_loop(t_philo *tab, t_data *data, int nb)
{
	int	i;
	int	todo;

	i = -1;
	todo = data->nb_philo;
	ft_usleep(3);
	while (todo)
	{
		i = (i + 1) % nb;
		pthread_mutex_lock(&tab[i].mutex);
		if (!(tab[i].finish && data->must_eat))
			todo = data->nb_philo;
		else
			--todo;
		if (ft_get_time(0) > tab[i].last_eat + data->time_to_die)
		{
			ft_log(i, 4);
			pthread_mutex_unlock(&tab[i].mutex);
			return ;
		}
		pthread_mutex_unlock(&tab[i].mutex);
	}
}

static int	philo_init(t_philo *tab, int i, t_data	*data)
{
	tab[i].id = i;
	tab[i].data = data;
	if (pthread_mutex_init(&tab[i].mutex, 0))
		return (1);
	if (pthread_create(&(tab[i].philo), 0, ft_philo, tab + i))
	{
		pthread_mutex_destroy(&tab[i].mutex);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;
	int		nb;
	t_philo	*tab;

	tab = 0;
	if (data_init(&data, ac - 1, av + 1))
		return (0);
	nb = data.nb_philo;
	tab = ft_calloc(nb + 1, sizeof(t_philo));
	if (!tab)
		return (ft_exit(&data, tab));
	i = -1;
	ft_get_time(1);
	while (++i < nb)
		if (philo_init(tab, i, &data))
			return (ft_exit(&data, tab));
	philo_loop(tab, &data, nb);
	return (ft_exit(&data, tab));
}
