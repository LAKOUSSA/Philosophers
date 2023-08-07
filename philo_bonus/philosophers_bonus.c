/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:23:49 by gloukas           #+#    #+#             */
/*   Updated: 2023/06/22 03:50:04 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	fill_state(t_info *state, int ac, char **av)
{
	int	i;

	state->nop = ft_atoi(av[1]);
	state->time_to_die = ft_atoi(av[2]);
	state->time_to_eat = ft_atoi(av[3]);
	state->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		state->must_eat = ft_atoi(av[5]);
	else
		state->must_eat = -1;
	state->stop = 0;
	state->each_ph = malloc(sizeof(t_ph) * (state->nop + 1));
	if (!state->each_ph)
		error("	❌ Allocating memory for philosophers");
	i = -1;
	while (++i < state->nop)
	{
		state->each_ph[i].meals = 0;
		state->each_ph[i].index = i;
		gettimeofday(&(state->each_ph[i].last_meal), NULL);
		state->each_ph[i].info = state;
	}
	create__semaphores(state);
}

void	create__processus_pair(t_info *state)
{
	t_need	h;

	h.i = 0;
	while (h.i < state->nop)
	{
		state->each_ph[h.i].id = fork();
		if (state->each_ph[h.i].id < 0)
			error("Creating philosopher process.");
		else if (state->each_ph[h.i].id == 0)
			philosopher(&state->each_ph[h.i]);
		(h.i) += 2;
	}
	usleep(200);
	create__processus_impair(&h, &state);
	h.i = 0;
	h.cnt = 0;
	start_processus(&h, &state);
}

void	create__processus_impair(t_need *h, t_info **state)
{
	h->i = 1;
	while (h->i < (*state)->nop)
	{
		(*state)->each_ph[h->i].id = fork();
		if ((*state)->each_ph[h->i].id < 0)
			error("Creating philosopher process.");
		else if ((*state)->each_ph[h->i].id == 0)
			philosopher(&(*state)->each_ph[h->i]);
		(h->i) += 2;
	}
}

void	start_processus(t_need *h, t_info **state)
{
	while (h->i < (*state)->nop && h->cnt < (*state)->nop)
	{
		h->p = 0;
		h->terminat_pid = waitpid((*state)->each_ph[h->i].id, &(h->p), WNOHANG);
		h->a = WIFEXITED(h->p);
		if (h->terminat_pid && h->a)
		{
			h->exit_status = WEXITSTATUS(h->p);
			if (h->exit_status == 1)
			{
				h->i = -1;
				while (++(h->i) < (*state)->nop)
					kill((*state)->each_ph[h->i].id, SIGKILL);
				break ;
			}
			else if (h->exit_status == 11)
			{
				h->cnt++;
				kill((*state)->each_ph[h->i].id, SIGKILL);
			}
		}
		h->i = ((h->i) + 1) % (*state)->nop;
	}
}

void	philosopher(t_ph *philo)
{
	t_info		*state;
	pthread_t	help;

	state = philo->info;
	pthread_create(&help, NULL, death, philo);
	pthread_detach(help);
	while (1)
	{
		eating(philo->index, state);
		print_color_event(get_time(), philo->index + 1, "is Sleeping", state);
		ft_sleep(state->time_to_sleep);
		print_color_event(get_time(), philo->index + 1, "is Thinking", state);
	}
}
