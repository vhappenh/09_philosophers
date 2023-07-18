/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:37:34 by vhappenh          #+#    #+#             */
/*   Updated: 2023/07/18 16:14:32 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	ft_join_threads(t_philo *p_stats, int n_threads)
{
	int	i;

	if (n_threads != -1)
	{
		i = -1;
		while (++i < n_threads)
		{
			if (pthread_join(p_stats[i].philo, NULL))
			{
				write(2, "Failed to join thread.\n", 24);
				return (true);
			}
		}
	}
	return (false);
}

bool	ft_free(t_meta *meta, t_philo *p_stats, int i)
{
	if (ft_join_threads(p_stats, i))
		return (true);
	i = -1;
	if (p_stats)
		while (++i < (int)meta->n)
			pthread_mutex_destroy(&p_stats[i].mutex);
	free (p_stats);
	if (meta)
	{
		pthread_mutex_destroy(&meta->print);
		pthread_mutex_destroy(&meta->dead_protect);
	}
	return (false);
}
