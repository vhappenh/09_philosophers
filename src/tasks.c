/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:03:17 by vhappenh          #+#    #+#             */
/*   Updated: 2023/07/18 16:15:01 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	release_forks(t_philo *philo)
{
	if (philo->hands == 2)
	{
		pthread_mutex_lock(philo->mutex_n);
		*philo->fork_n = true;
		pthread_mutex_unlock(philo->mutex_n);
		pthread_mutex_lock(&philo->mutex);
		philo->fork = true;
		pthread_mutex_unlock(&philo->mutex);
		philo->hands = 0;
		ft_print(philo, "is sleeping\n");
		philo->tts = ft_get_time() + philo->meta->tts;
		while (1)
		{
			usleep (50);
			if (ft_monitoring(philo))
				return (1);
			if (philo->tts <= ft_get_time())
			{
				ft_print(philo, "is thinking\n");
				break ;
			}
		}
	}
	return (0);
}

int	set_eat_times(t_philo *philo)
{
	unsigned long	t;

	t = ft_get_time();
	philo->ttd = philo->meta->ttd + t;
	philo->tte = philo->meta->tte + t;
	ft_print(philo, "is eating\n");
	while (1)
	{
		usleep (50);
		if (ft_monitoring(philo))
			return (1);
		if (philo->tte <= ft_get_time())
		{
			philo->nom--;
			if (philo->nom == 0)
			{
				pthread_mutex_lock(&philo->meta->meal_protect);
				philo->meta->meals_eaten++;
				pthread_mutex_unlock(&philo->meta->meal_protect);
			}
			break ;
		}
	}
	return (0);
}

int	grab_o_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	if (philo->fork == true)
	{
		ft_print(philo, "has taken a fork\n");
		philo->fork = false;
		pthread_mutex_unlock(&philo->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex);
	return (0);
}

int	grab_n_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_n);
	if (*philo->fork_n == true)
	{
		ft_print(philo, "has taken a fork\n");
		*philo->fork_n = false;
		pthread_mutex_unlock(philo->mutex_n);
		return (1);
	}
	pthread_mutex_unlock(philo->mutex_n);
	return (0);
}

int	grab_forks(t_philo *philo)
{
	if (philo->index % 2)
	{
		philo->hands += grab_n_fork(philo);
		if (philo->hands == 1)
			philo->hands += grab_o_fork(philo);
	}
	else
	{
		philo->hands += grab_o_fork(philo);
		if (philo->hands == 1)
			philo->hands += grab_n_fork(philo);
	}
	if (philo->hands == 2)
		if (set_eat_times(philo))
			return (1);
	return (0);
}
