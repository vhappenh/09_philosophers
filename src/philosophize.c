/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:05:11 by vhappenh          #+#    #+#             */
/*   Updated: 2023/07/19 12:47:56 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_solophilo(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->fork = false;
	pthread_mutex_unlock(&philo->mutex);
	ft_print(philo, "has taken a fork\n");
	while (1)
		if (ft_monitor_death(philo))
			return ;
	return ;
}

static int	ft_multiphilo(t_philo *philo)
{
	if (philo->index % 2)
		usleep(5);
	while (1)
	{
		if (grab_forks(philo))
			return (1);
		if (release_forks(philo))
			return (1);
		if (ft_monitoring(philo))
			return (1);
	}
	return (0);
}

void	*ft_start(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	philo->ttd = philo->meta->ttd + ft_get_time();
	if (philo->meta->n == 1)
	{
		ft_solophilo(philo);
		return (NULL);
	}
	if (ft_multiphilo(philo))
		return (NULL);
	return (NULL);
}

bool	ft_thread_create(int n, t_meta *meta, t_philo **p_stats, int *i)
{
	if (ft_setup_p_stats(meta, p_stats, i))
		return (true);
	meta->start_time = ft_get_time();
	*i = -1;
	while (++(*i) < n)
	{
		if (pthread_create(&((*p_stats)[*i].philo), NULL, &ft_start,
			&((*p_stats)[*i])))
		{
			pthread_mutex_lock(&meta->dead_protect);
			meta->dead = true;
			pthread_mutex_unlock(&meta->dead_protect);
			write(2, "Problem while creating threads.\n", 33);
			return (true);
		}
	}
	return (false);
}
