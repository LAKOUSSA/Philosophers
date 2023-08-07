/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 21:36:11 by gloukas           #+#    #+#             */
/*   Updated: 2023/06/20 18:59:04 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death(t_info *state)
{
	t_ph	*philo;
	int		i;

	i = -1;
	while (++i < state->nop)
	{
		pthread_mutex_lock(&(state->check));
		if (state->exit >= state->nop)
		{
			pthread_mutex_unlock(&(state->check));
			return (1);
		}
		philo = &state->each_ph[i];
		if (get_time() - philo->last_eat > state->time_to_die)
		{
			print_color_event(get_time(), philo->index, "is Died", state);
			pthread_mutex_lock(&(state->print));
			state->stop = 1;
			pthread_mutex_unlock(&(state->print));
			pthread_mutex_unlock(&(state->check));
			return (1);
		}
		pthread_mutex_unlock(&(state->check));
	}
	return (0);
}

int	fill_args(t_info *state, int ac, char **av)
{
	state->nop = ft_atoi(av[1]);
	if (state->nop == -7)
		return (-7);
	state->time_to_die = ft_atoi(av[2]);
	if (state->time_to_die == -7)
		return (-7);
	state->time_to_eat = ft_atoi(av[3]);
	if (state->time_to_eat == -7)
		return (-7);
	state->time_to_sleep = ft_atoi(av[4]);
	if (state->time_to_sleep == -7)
		return (-7);
	if (ac == 6)
		state->must_eat = ft_atoi(av[5]);
	else
		state->must_eat = -1;
	if (state->must_eat == -7 || state->must_eat == 0)
		return (-7);
	return (1);
}

int	fill_state(t_info *state)
{
	state->stop = 0;
	state->exit = 0;
	state->chopstick = (pthread_mutex_t *)malloc(state->nop
			* sizeof(pthread_mutex_t));
	if (!state->chopstick)
	{
		error("	❌ Allocating memory for chopstick");
		return (-7);
	}
	state->each_ph = malloc(sizeof(t_ph) * (state->nop + 1));
	if (!state->each_ph)
	{
		free(state->chopstick);
		error("	❌ Allocating memory for philosophers");
		return (-7);
	}
	pthread_mutex_init(&(state->print), NULL);
	pthread_mutex_init(&(state->check), NULL);
	return (1);
}

void	start_thread(t_info *state)
{
	int		i;
	t_ph	*philo;

	i = -1;
	while (++i < state->nop)
	{
		state->each_ph[i].last_eat = get_time();
		pthread_mutex_init(&(state->chopstick[i]), NULL);
	}
	state->init = get_time();
	i = -1;
	while (++i < state->nop)
	{
		philo = &state->each_ph[i];
		philo->index = i + 1;
		philo->left_chopstick = i;
		philo->right_chopstick = (i + 1) % state->nop;
		philo->meals = 0;
		philo->info = state;
		pthread_create(&philo->id, NULL, philosopher, philo);
	}
	while (1)
		if (death(state))
			break ;
}

void	*philosopher(void *param)
{
	t_ph	*philo;
	t_info	*state;

	philo = (t_ph *)param;
	state = philo->info;
	if ((philo->index % 2))
		usleep(100);
	while (1)
	{
		eating(philo);
		pthread_mutex_lock(&(state->check));
		if (philo->meals >= state->must_eat && state->must_eat != -1)
		{
			state->exit++;
			pthread_mutex_unlock(&(state->check));
			break ;
		}
		pthread_mutex_unlock(&(state->check));
		print_color_event(get_time(), philo->index, "is Sleeping", state);
		ft_sleep(state->time_to_sleep);
		print_color_event(get_time(), philo->index, "is Thinking", state);
	}
	return (NULL);
}
