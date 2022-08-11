/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:19:30 by jalamell          #+#    #+#             */
/*   Updated: 2022/08/11 15:24:31 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>

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
	long	ret;
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
