/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:22:51 by gloukas           #+#    #+#             */
/*   Updated: 2023/06/22 03:49:02 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/*==================structs==================*/

typedef struct s_info
{
	int				nop;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				must_eat;
	unsigned long	init;
	int				stop;
	int				exit;
	sem_t			*chopstick;
	sem_t			*print;
	sem_t			*check;
	struct s_ph		*each_ph;
}					t_info;

typedef struct s_ph
{
	pid_t			id;
	int				index;
	struct timeval	last_meal;
	int				meals;
	struct s_info	*info;
}					t_ph;

typedef struct s_need
{
	int				i;
	int				p;
	int				terminat_pid;
	int				exit_status;
	int				cnt;
	int				a;
}					t_need;

/*==================parsin_bonus.c==================*/

void				error(char *s);
int					ft_atoi(char *str);
void				check_args(int ac, char **av);
void				cleanup_semaphores(t_info *state);
void				ft_sleep(unsigned long x);

/*==================events_bonus.c==================*/

unsigned long		get_time(void);
void				print_color_event(unsigned long time, int i, char *s,
						t_info *state);
void				eating(int i, t_info *state);
void				create__semaphores(t_info *state);
void				*death(void *arg);

/*===============philosophers_bonus.c===============*/

void				fill_state(t_info *state, int ac, char **av);
void				create__processus_pair(t_info *state);
void				create__processus_impair(t_need *h, t_info **state);
void				start_processus(t_need *h, t_info **state);
void				philosopher(t_ph *philo);

/*===================main_bonus.c===================*/
//+main

#endif
