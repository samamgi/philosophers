/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:52:32 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/09/08 09:48:56 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_error(const char *error)
{
	printf("error : %s\n", error);
	exit(EXIT_FAILURE);
}

long	gettime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		exit_error("gettimeofday issue");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long time, t_data_table *table)
{
	long	start;
	long	during;
	long	rest;

	start = gettime();
	while (gettime() - start < time)
	{
		if (is_finished(table) == true)
			break ;
		during = gettime() - start;
		rest = time - during;
		if (rest > 10)
			usleep((rest / 2) * 1000);
		else
		{
			while (gettime() - start < time)
				;
		}
	}
}

void	add_long(pthread_mutex_t *mutex, long *nbr)
{
	safe_mutex_handle(mutex, LOCK);
	(*nbr)++;
	safe_mutex_handle(mutex, UNLOCK);
}

void	clear_all(t_data_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->philo_mutex_safe, DESTROY);
		i++;
	}
	safe_mutex_handle(&table->write_mutex_safe, DESTROY);
	safe_mutex_handle(&table->table_mutex_safe, DESTROY);
	free(table->fourchettes);
	free(table->philos);
}
