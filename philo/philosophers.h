/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:47:39 by gloukas           #+#    #+#             */
/*   Updated: 2023/06/22 04:26:11 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/*==================structs==================*/

typedef struct s_ph
{
	pthread_t		id;
	int				index;
	int				left_chopstick;
	int				right_chopstick;
	long			last_eat;
	int				meals;
	struct s_info	*info;
}					t_ph;

typedef struct s_info
{
	int				nop;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat;
	long			init;
	int				stop;
	int				exit;
	pthread_mutex_t	*chopstick;
	pthread_mutex_t	print;
	pthread_mutex_t	check;
	t_ph			*each_ph;
}					t_info;

/*==================parsin.c==================*/

void				error(char *s);
int					atoi_help(char *str, int i);
int					ft_atoi(char *str);
int					check_args(int ac, char **av);

/*==================events.c==================*/

long				get_time(void);
void				print_color_event(long time, int i, char *s, t_info *state);
void				eating(t_ph *philo);
void				ft_sleep(long x);

/*===============philosophers.c===============*/

int					death(t_info *state);
int					fill_args(t_info *state, int ac, char **av);
int					fill_state(t_info *state);
void				start_thread(t_info *state);
void				*philosopher(void *param);

/*===================main.c===================*/
//+main

#endif
