/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:57:52 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/09/10 20:57:54 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "./libft/libft.h"
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_LEFT_FORK,
	TAKE_RIGHT_FORK,
	DIED,
}							t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}							t_opcode;

typedef struct s_data_table	t_data_table;

typedef struct s_fourchette
{
	pthread_mutex_t			fourchette;
	int						fourchette_id;
}							t_fourchette;

typedef struct s_philo
{
	int						id;
	long					meals;
	bool					max;
	long					last_meal_time;
	t_fourchette			*right_fourchette;
	t_fourchette			*left_fourchette;
	pthread_t				thread_philo_id;
	pthread_mutex_t			philo_mutex_safe;
	t_data_table			*table;
}							t_philo;

struct						s_data_table
{
	long					philo_nbr;
	long					time_die;
	long					time_eat;
	long					time_sleep;
	long					limit_meals;
	long					time_start;
	bool					end;
	bool					sync_philos_threads;
	long					size_threads_run;
	pthread_mutex_t			table_mutex_safe;
	pthread_mutex_t			write_mutex_safe;
	pthread_t				monitor;
	t_fourchette			*fourchettes;
	t_philo					*philos;
};

void						exit_error(const char *error);

void						print_table(t_data_table table);

int							parse_table(t_data_table *table, char **av);

void						safe_thread_handle(pthread_t *thread,
								void *(*fct)(void *), void *data,
								t_opcode status);

void						safe_mutex_handle(pthread_mutex_t *mutex,
								t_opcode etat);

void						table_init(t_data_table *table);

void						init_start(t_data_table *table);

bool						is_finished(t_data_table *data);

long						read_long(pthread_mutex_t *mutex, long *to_read);

void						write_long(pthread_mutex_t *mutex, long *to_write,
								long new);

bool						read_bool(pthread_mutex_t *mutex, bool *to_read);

void						write_bool(pthread_mutex_t *mutex, bool *to_write,
								bool new);

long						gettime(void);

void						ft_usleep(long time, t_data_table *table);

void						print_doing(t_philo_status doing, t_philo *philo);

void						add_long(pthread_mutex_t *mutex, long *nbr);

bool						is_running(pthread_mutex_t *mutex, long *threads,
								long philos);

void						*monitor(void *data);

void						clear_all(t_data_table *table);

void						unsynch_philo(t_philo *philo);

void						think(t_philo *philo, bool fair);

void						sync_philos_threads(t_data_table *table);

void						init_annex(t_data_table *table);

void						unsynch_philo(t_philo *philo);

#endif