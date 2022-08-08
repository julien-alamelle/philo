#include <pthread.h>

typedef struct s_fork
{
	int				nb_philo;
	pthread_mutex_t	*forks;
}	t_fork;

static void	*fork_delete(t_fork fork, int nb_to_delete)
{
	if (!fork)
		return (0);
	if (nb_to_delete >= 0 && fork->forks)
	{
		while (nb_to_delete--)
			phtread_mutex_delete(fork->forks + nb_to_delete);
		free(fork->forks);
	}
	free(fork)
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

void	ft_eat(void *fork, int id)
{
	t_fork *const	tfork = fork;
	pthread_mutex_t	*m1;
	pthread_mutex_t	*m2;

	if (id)
		m1 = tfork->forks + id - 1;
	else
		m1 = tfork->forks + tfork->nb_philo - 1;
	m2 = m1;
	if (id % 2)
		m1 = tfork->forks + id;
	else
		m2 = tfork->forks + id;
	pthread_mutex_lock(m1);
	ft_log(id, 0);
	pthread_mutex_lock(m2);
	ft_log(id, 0);
	ft_log(id, 1);
	pthread_mutex_lock(m1);
	pthread_mutex_lock(m2);
}

void	*ft_fork_delete(void *fork)
{
	t_fork *const	tfork = fork;

	return (fork_delete(tfork, tfork->nb_philo));
}
