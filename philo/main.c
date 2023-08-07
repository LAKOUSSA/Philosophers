/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:55:47 by gloukas           #+#    #+#             */
/*   Updated: 2023/06/22 04:26:08 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_info	*state;
	int		i;

	i = 0;
	i = 0;
	if (!check_args(ac, av))
		return (0);
	if (!ft_atoi(av[1]))
		return (0);
	state = malloc(sizeof(t_info));
	if (!state)
		error("	❌ Allocating memory for State");
	if (fill_args(state, ac, av) == -7)
		return (0);
	if (fill_state(state) < 0)
		return (0);
	printf("\e\033[1;32m| 🔰 EVENTS	OF	PHILOSOPHERS 🔰 |\e[0m\n\n");
	start_thread(state);
	i = -1;
	while (++i < state->nop)
		pthread_detach(state->each_ph[i].id);
	return (0);
}
