/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:23:44 by gloukas           #+#    #+#             */
/*   Updated: 2023/06/22 03:52:29 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	error(char *s)
{
	printf("ERROR\n\033[1;31m%s\n\e[0m", s);
	exit(1);
}

int	ft_atoi(char *str)
{
	int	i;
	int	r;

	r = 0;
	i = 0;
	while (str && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '\0' || str[i] == '-')
		error("	❌ Format of arguments.");
	if (str && str[i] == '+')
	{
		if (str[i + 1] == '+' || str[i + 1] == '\0')
			error("	❌ Format of arguments.");
		i++;
	}
	while (str && str[i] >= '0' && str[i] <= '9')
	{
		if (r * 10 + str[i] - 48 < r)
			error("	❌ Format of arguments.");
		r = r * 10 + str[i] - 48;
		i++;
	}
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		error("	❌ Format of arguments.");
	return (r);
}

void	check_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 6 && ac != 5)
		error("	❌ Number of  arguments.");
	while (++i < ac)
		if (av[i][0] == '\0')
			error("	❌ Format of arguments.");
}

void	cleanup_semaphores(t_info *state)
{
	int	i;

	i = -1;
	sem_close(state->print);
	sem_close(state->chopstick);
	sem_close(state->check);
	sem_unlink("printy");
	sem_unlink("chopsticky");
	sem_unlink("checky");
	free(state->each_ph);
	free(state);
}

void	ft_sleep(unsigned long x)
{
	unsigned long	i;

	i = get_time();
	while (get_time() - i <= x)
		usleep(100);
}
