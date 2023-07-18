/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:00:24 by vhappenh          #+#    #+#             */
/*   Updated: 2023/06/18 15:54:02 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_atoi_helper(const char *nptr, int *sign, int *i)
{
	while ((nptr[*i] <= 13 && nptr[*i] > 8) || nptr[*i] == 32)
		(*i)++;
	if (nptr[*i] == '+' || nptr[*i] == '-')
	{
		if (nptr[*i] == '-')
			*sign = *sign * -1;
		(*i)++;
	}
}

long	ft_atol(const char *nptr)
{
	long			sum;
	int				i;
	int				sign;
	long			temp;

	i = 0;
	sum = 0;
	sign = 1;
	ft_atoi_helper(nptr, &sign, &i);
	if (!(nptr[i] >= '0' && nptr[i] <= '9'))
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		temp = sum;
		sum = sum * 10 + nptr[i] - '0';
		if (sum < temp && ((sum != INT_MIN && sign == -1)
				|| (sum == INT_MIN && sign != -1)))
			return (sum);
		i++;
	}
	return (sum * sign);
}

unsigned long	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_print(t_philo *philo, char *str)
{
	unsigned long	t;

	t = ft_get_time() - philo->meta->start_time;
	pthread_mutex_lock(&philo->meta->print);
	printf("%ld %d %s", t, philo->index + 1, str);
	pthread_mutex_unlock(&philo->meta->print);
	return ;
}
