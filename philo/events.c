/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:29:25 by gloukas           #+#    #+#             */
/*   Updated: 2023/06/20 18:57:23 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (1000 * tv.tv_sec) + (tv.tv_usec / 1000);
	return (time);
}

void	print_color_event(long time, int i, char *s, t_info *state)
{
	long	curr;

	pthread_mutex_lock(&(state->print));
	curr = time - state->init;
	if (!state->stop)
		printf("%lu Philosopher %d %s\n", curr, i, s);
	pthread_mutex_unlock(&(state->print));
}

void	eating(t_ph *philo)
{
	t_info	*state;

	state = philo->info;
	pthread_mutex_lock(&(state->chopstick[philo->left_chopstick]));
	print_color_event(get_time(), philo->index, "take Left Chopstick", state);
	pthread_mutex_lock(&(state->chopstick[philo->right_chopstick]));
	print_color_event(get_time(), philo->index, "take Right Chopstick", state);
	print_color_event(get_time(), philo->index, "is Eating", state);
	pthread_mutex_lock(&(state->check));
	philo->last_eat = get_time();
	pthread_mutex_unlock(&(state->check));
	ft_sleep(state->time_to_eat);
	philo->meals++;
	pthread_mutex_unlock(&(state->chopstick[philo->left_chopstick]));
	pthread_mutex_unlock(&(state->chopstick[philo->right_chopstick]));
}

void	ft_sleep(long x)
{
	long	i;

	i = get_time();
	while (get_time() - i <= x)
		usleep(100);
}
