/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:01:35 by vhappenh          #+#    #+#             */
/*   Updated: 2023/06/18 13:55:47 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_for_minmax(char **av)
{
	int	i;

	if (ft_atol(av[0]) > 400)
	{
		write(2, "Too many philosophers!\n", 23);
		return (true);
	}
	else if (ft_atol(av[0]) <= 0)
	{
		write(2, "Minimum of 1 philosopher needed!\n", 33);
		return (true);
	}
	i = 0;
	while (av[++i])
	{
		if (ft_atol(av[i]) > INT_MAX)
		{
			write(2, "Please stay in positive int range!\n", 36);
			return (true);
		}
	}
	return (false);
}

bool	check_for_digit(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		if (!av[i][0])
		{
			write(2, "Invalid input. No empty strings allowed!\n", 42);
			return (true);
		}
		while (av[i][++j])
		{
			if (!(av[i][j] <= '9' && av[i][j] >= '0'))
			{
				write(2, "Invalid input. Only numbers allowed!\n", 38);
				return (true);
			}
		}
	}
	return (false);
}

bool	check_nb_arguments(int ac)
{
	if (ac == 1)
	{
		write(2, "Need arguments: nb, ttd, tte, tts, [nom]\n", 42);
		return (true);
	}
	if (ac != 5 && ac != 6)
	{
		write(2, "Wrong ammount of arguments. Need 4 or 5\n", 41);
		return (true);
	}
	return (false);
}
