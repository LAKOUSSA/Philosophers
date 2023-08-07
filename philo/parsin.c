/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:00:12 by gloukas           #+#    #+#             */
/*   Updated: 2023/06/22 04:26:15 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error(char *s)
{
	printf("ERROR\n\033[1;31m%s\n\e[0m", s);
}

int	atoi_help(char *str, int i)
{
	while (str && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '\0' || str[i] == '-')
	{
		error("	❌ Format of arguments.");
		return (-7);
	}
	if (str[i] && str[i] == '+')
	{
		if (str[i + 1] == '+' || str[i + 1] == '\0')
		{
			error("	❌ Format of arguments.");
			return (-7);
		}
		i++;
	}
	return (i);
}

int	ft_atoi(char *str)
{
	int	i;
	int	r;

	r = 0;
	i = 0;
	i = atoi_help(str, i);
	if (i == -7)
		return (-7);
	while (str && str[i] >= '0' && str[i] <= '9')
	{
		if (r * 10 + str[i] - 48 < r)
		{
			error("	❌ Format of arguments.");
			return (-7);
		}
		r = r * 10 + str[i] - 48;
		i++;
	}
	if (str[i] && (str[i] < '0' || str[i] > '9'))
	{
		error("	❌ Format of arguments.");
		return (-7);
	}
	return (r);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 6 && ac != 5)
	{
		error("	❌ Number of  arguments.");
		return (0);
	}
	while (++i < ac)
	{
		if (av[i][0] == '\0')
		{
			error("	❌ Format of arguments.");
			return (0);
		}
	}
	return (1);
}
