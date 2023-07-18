/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:42:52 by vhappenh          #+#    #+#             */
/*   Updated: 2023/06/18 14:21:39 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_monitor_death(t_philo *philo)
{
	if (ft_get_time() > philo->ttd)
	{
		pthread_mutex_lock(&philo->meta->dead_protect);
		if (philo->meta->dead == false)
		{
			ft_print(philo, "died\n");
			philo->meta->dead = true;
		}
		pthread_mutex_unlock(&philo->meta->dead_protect);
		return (1);
	}
	return (0);
}

static int	ft_someone_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->meta->dead_protect);
	if (philo->meta->dead == true)
	{
		pthread_mutex_unlock(&philo->meta->dead_protect);
		return (1);
	}
	pthread_mutex_unlock(&philo->meta->dead_protect);
	return (0);
}

static int	ft_monitor_mealnumber(t_philo *philo)
{
	pthread_mutex_lock(&philo->meta->meal_protect);
	if (philo->meta->meals_eaten == (int)philo->meta->n)
	{
		pthread_mutex_unlock(&philo->meta->meal_protect);
		return (1);
	}
	pthread_mutex_unlock(&philo->meta->meal_protect);
	return (0);
}

int	ft_monitoring(t_philo *philo)
{
	if (ft_monitor_death(philo))
		return (1);
	if (ft_someone_dead(philo))
		return (1);
	if (ft_monitor_mealnumber(philo))
		return (1);
	return (0);
}
