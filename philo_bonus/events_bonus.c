/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:23:28 by gloukas           #+#    #+#             */
/*   Updated: 2023/06/24 04:35:34 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

unsigned long	get_time(void)
{
	struct timeval	tv;
	long			time;

	if (gettimeofday(&tv, NULL))
		error("	❌ Gettimeofday() FAILURE.");
	time = (1000 * tv.tv_sec) + (tv.tv_usec / 1000);
	return (time);
}

void	print_color_event(unsigned long time, int i, char *s, t_info *state)
{
	sem_wait(state->print);
	printf("%lu Philosopher %d %s\n", time - state->init, i, s);
	sem_post(state->print);
}

void	eating(int i, t_info *state)
{
	sem_wait(state->chopstick);
	print_color_event(get_time(), i + 1, "has taken a fork", state);
	sem_wait(state->chopstick);
	print_color_event(get_time(), i + 1, "has taken a fork", state);
	gettimeofday(&(state->each_ph[i].last_meal), NULL);
	print_color_event(get_time(), i + 1, "is Eating", state);
	state->each_ph[i].meals++;
	ft_sleep(state->time_to_eat);
	if (state->each_ph[i].meals >= state->must_eat && state->must_eat != -1)
	{
		sem_post(state->chopstick);
		sem_post(state->chopstick);
		exit(11);
	}
	sem_post(state->chopstick);
	sem_post(state->chopstick);
}

void	create__semaphores(t_info *state)
{
	sem_unlink("printy");
	sem_unlink("chopsticky");
	sem_unlink("checky");
	state->chopstick = sem_open("chopsticky", O_CREAT, 0600, state->nop);
	state->print = sem_open("printy", O_CREAT, 0600, 1);
	state->check = sem_open("checky", O_CREAT, 0600, 1);
	if (state->print == SEM_FAILED || state->chopstick == SEM_FAILED
		|| state->check == SEM_FAILED)
		error("❌ Failed to create semaphores");
	state->init = get_time();
}

void	*death(void *arg)
{
	t_ph	*philo;

	philo = (t_ph *)arg;
	while (1)
	{
		sem_wait(philo->info->check);
		if (get_time() - ((philo->last_meal.tv_sec * 1000)
				+ (philo->last_meal.tv_usec / 1000)) > philo->info->time_to_die)
		{
			sem_wait(philo->info->print);
			printf("%lu Philosopher %d is Died \n", get_time()
				- philo->info->init, philo->index + 1);
			exit(1);
		}
		usleep(100);
		sem_post(philo->info->check);
	}
	return (NULL);
}
