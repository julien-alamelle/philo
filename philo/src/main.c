#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include "philo.h"

void	*ft_calloc(int nb_blocks, int size_blocks)
{
	char	*ret;
	double	total_size;

	total_size = nb_blocks * size_blocks;
	if (total_size <= 0 || total_size > INT_MAX)
		return (0);
	ret = malloc(total_size);
	while (total_size--)
		ret[(int)total_size] = 0;
	return ((void *)ret);
}

int	ft_atoi(char *str)
{
	double	ret;
	int		sign;

	if (!str)
		return (0);
	sign = 1;
	ret = 0;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		++str;
	}
	while (*str >= '0' && *str <= '9')
	{
		ret = 10 * ret + sign * (*(str++) - '0');
		if (ret > INT_MAX || ret < INT_MIN)
			return (-1);
	}
	if (*str)
		ret = -1;
	return (ret);
}

void	*philo(void *arg)
{
	int				nb;
	t_data *const	data = arg;

	nb = ++(data->nb_philo);
	while(nb--)
			++(data->must_eat);
	return (arg);
}

t_data	*data_init(int ac, char **av)
{
	t_data	*ret;

	if (ac < 4 || ac > 5)
	{
		dprintf(2, "Error: Require 4 or 5 arguments\n");
		return (0);
	}
	ret = malloc(sizeof(t_data));
	if (!ret)
		return (0);
	ret->nb_philo = ft_atoi(av[0]);
	ret->time_to_die = ft_atoi(av[1]);
	ret->time_to_eat = ft_atoi(av[2]);
	ret->time_to_sleep = ft_atoi(av[3]);
	ret->must_eat = ft_atoi(av[4]);
	gettimeofday(&(ret->time_start), 0);
	if (ret->nb_philo < 1 || ret->time_to_die < 0 || ret->time_to_eat < 0
		|| ret->time_to_sleep < 0 || ret->must_eat < 0)
	{
		free(ret);
		ret = 0;
		if (ret->nb_philo < 1 || ret->time_to_die < 0 || ret->time_to_eat < 0
			|| ret->time_to_sleep < 0)
		dprintf(2, "Error: Bad arguments");
	}
	return (ret);
}

int	ft_exit(t_data *data, pthread_t *tab)
{
	int	i;

	if (data)
	{
		data->nb_philo = 0;
		if (tab)
		{
			i = -1;
			while (tab[++i])
				pthread_join(tab[i], 0);
			free(tab);
		}
dprintf(1, "%d\n", data->must_eat);
		free(data);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data		*data;
	int			i;
	int			nb;
	pthread_t	*tab;

	tab = 0;
	if (ac == 6 && ft_atoi(av[5]) <= 0)
		return (0);
	data = data_init(ac - 1, av + 1);
	if (!data)
		return (ft_exit(data, tab));
	nb = data->nb_philo;
	data->nb_philo = 0;
	tab = ft_calloc(nb + 1, sizeof(pthread_t));
	if (!tab)
		return (ft_exit(data, tab));
	i = -1;
	while (++i < nb)
		if (pthread_create(tab + i, 0, philo ,data))
			return (ft_exit(data, tab));
	ft_exit(data, tab);
	return (0);
}
