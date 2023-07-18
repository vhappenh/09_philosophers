/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:35:27 by vhappenh          #+#    #+#             */
/*   Updated: 2023/07/18 15:56:06 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	ft_philosophers(char **input, t_meta *meta)
{
	t_philo	*p_stats;
	int		i;

	i = -1;
	if (ft_philo_prep(input, meta, &p_stats))
		return (ft_free(meta, p_stats, i));
	if (ft_thread_create(ft_atol(input[0]), meta, &p_stats, &i))
		return (ft_free(meta, p_stats, i));
	ft_free(meta, p_stats, i);
	return (false);
}

bool	input_check(int ac, char **av)
{
	if (check_nb_arguments(ac))
		return (true);
	if (check_for_digit(av))
		return (true);
	if (check_for_minmax(av))
		return (true);
	return (false);
}

int	main(int ac, char **av)
{
	t_meta	meta;

	if (input_check(ac, &av[1]))
		return (1);
	if (ft_philosophers(&av[1], &meta))
		return (2);
	return (0);
}
