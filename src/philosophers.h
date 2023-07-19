/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:35:25 by vhappenh          #+#    #+#             */
/*   Updated: 2023/07/19 13:03:44 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_meta
{
	unsigned long	ttd;
	unsigned long	tte;
	unsigned long	tts;
	int				nom;
	unsigned int	n;
	unsigned int	max_index;
	long			start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	dead_protect;
	bool			dead;
	pthread_mutex_t	meal_protect;
	int				meals_eaten;
}	t_meta;

typedef struct s_philosopher
{
	pthread_t		philo;
	unsigned long	ttd;
	unsigned long	tte;
	unsigned long	tts;
	int				nom;
	unsigned int	index;
	unsigned int	nbr;
	pthread_mutex_t	mutex;
	bool			fork;
	int				hands;
	pthread_mutex_t	*mutex_n;
	bool			*fork_n;
	t_meta			*meta;
}	t_philo;

/* input check */
bool			check_nb_arguments(int ac);
bool			check_for_digit(char **av);
bool			check_for_minmax(char **av);

/* philosophers */
bool			ft_philo_prep(char **input, t_meta *meta, t_philo **p_stats);
bool			ft_thread_create(int n, t_meta *meta, t_philo **p_stats,
					int *i);
bool			ft_thread_join(int n, t_philo **philos);
bool			ft_setup_p_stats(t_meta *meta, t_philo **p_stats, int *i);
void			*ft_start(void *philo_struct);

/* tasks */
int				grab_forks(t_philo *philo);
int				set_eat_times(t_philo *philo);
int				release_forks(t_philo *philo);

/* monitoring */
int				ft_monitoring(t_philo *philo);
int				ft_monitor_death(t_philo *p_stats);

/* utils */
long			ft_atol(const char *nptr);
unsigned long	ft_get_time(void);
long			ft_get_timestamp(t_philo *philo);
void			ft_print(t_philo *philo, char *str);

/* free */
bool			ft_free(t_meta *meta, t_philo *p_stats, int i);

#endif