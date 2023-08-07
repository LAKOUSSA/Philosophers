/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:23:33 by gloukas           #+#    #+#             */
/*   Updated: 2023/06/22 03:52:09 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int ac, char **av)
{
	t_info	*state;

	check_args(ac, av);
	if (!ft_atoi(av[1]))
		return (0);
	state = malloc(sizeof(t_info));
	if (!state)
		error("	❌ Allocating memory for State");
	fill_state(state, ac, av);
	printf("\e\033[1;32m| 🔰 EVENTS	OF	PHILOSOPHERS 🔰 |\e[0m\n\n");
	create__processus_pair(state);
	cleanup_semaphores(state);
	return (0);
}
