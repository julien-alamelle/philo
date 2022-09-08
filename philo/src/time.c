/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:13:27 by jalamell          #+#    #+#             */
/*   Updated: 2022/09/08 14:15:05 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>

int	ft_get_time(int init)
{
	static struct timeval	start;
	struct timeval			curr;

	if (init)
	{
		gettimeofday(&start, 0);
		return (0);
	}
	gettimeofday(&curr, 0);
	return ((curr.tv_sec - start.tv_sec) * 1000
		+ (curr.tv_usec - start.tv_usec) / 1000);
}

void	ft_usleep(int time)
{
	const int	start = ft_get_time(0);
	int			done;

	usleep(800 * time);
	done = ft_get_time(0) - start;
	while (done < time)
	{
		usleep(500);
		done = ft_get_time(0) - start;
	}
}
