/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:22:59 by vhappenh          #+#    #+#             */
/*   Updated: 2023/08/18 17:06:04 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	ft_setup_meta_stats(char **input, int n, t_meta *meta)
{
	meta->ttd = ft_atol(input[1]);
	meta->tte = ft_atol(input[2]);
	meta->tts = ft_atol(input[3]);
	if (input[4])
		meta->nom = (int)ft_atol(input[4]);
	else
		meta->nom = 0;
	meta->n = n;
	meta->max_index = n - 1;
	if (pthread_mutex_init(&(meta->print), NULL))
		return (true);
	if (pthread_mutex_init(&(meta->dead_protect), NULL))
	{
		pthread_mutex_destroy(&(meta->print));
		return (true);
	}
	meta->dead = false;
	if (pthread_mutex_init(&(meta->meal_protect), NULL))
	{
		pthread_mutex_destroy(&(meta->print));
		pthread_mutex_destroy(&(meta->dead_protect));
		return (true);
	}
	meta->meals_eaten = 0;
	return (false);
}

static void	ft_get_neighbor(t_philo **p_stats, unsigned int i)
{
	if (i != 0)
	{
		(*p_stats)[i].mutex_n = &((*p_stats)[i - 1].mutex);
		(*p_stats)[i].fork_n = &((*p_stats)[i - 1].fork);
	}
	if (i == (*p_stats)[i].meta->max_index && (*p_stats)[i].meta->n != 1)
	{
		(*p_stats)[0].mutex_n = &((*p_stats)[i].mutex);
		(*p_stats)[0].fork_n = &((*p_stats)[i].fork);
	}
}

bool	ft_setup_p_stats(t_meta *meta, t_philo **p_stats, int *i)
{
	while (++(*i) < (int)meta->n)
	{
		(*p_stats)[*i].philo = 0;
		(*p_stats)[*i].index = *i;
		if (pthread_mutex_init(&((*p_stats)[*i].mutex), NULL))
			return (true);
		(*p_stats)[*i].fork = true;
		(*p_stats)[*i].hands = 0;
		(*p_stats)[*i].meta = meta;
		(*p_stats)[*i].nom = meta->nom;
		ft_get_neighbor(p_stats, *i);
	}
	return (false);
}

bool	ft_philo_prep(char **input, t_meta *meta, t_philo **p_stats)
{
	int			n;

	n = ft_atol(input[0]);
	if (ft_setup_meta_stats(input, n, meta))
		return (true);
	*p_stats = malloc(sizeof(t_philo) * n);
	memset(*p_stats, 0, sizeof(t_philo) * n);
	if (*p_stats == NULL)
		return (true);
	return (false);
}
