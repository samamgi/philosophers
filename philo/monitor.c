/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:09:40 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/09/09 19:09:53 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_running(pthread_mutex_t *mutex, long *threads, long philos)
{
	bool	res;

	res = false;
	safe_mutex_handle(mutex, LOCK);
	if ((*threads) == philos)
		res = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (res);
}

bool	is_dead(t_philo *philo)
{
	if (read_bool(&philo->philo_mutex_safe, &philo->max) == true)
		return (false);
	if ((gettime() - read_long(&philo->philo_mutex_safe,
				&philo->last_meal_time)) > philo->table->time_die)
		return (true);
	return (false);
}

void	*monitor(void *data)
{
	t_data_table	*table;
	int				i;

	table = (t_data_table *)data;
	while (is_running(&table->table_mutex_safe, &table->size_threads_run,
			table->philo_nbr) == false)
		ft_usleep(1000, table);
	while (is_finished(table) == false)
	{
		i = 0;
		while (i < table->philo_nbr && is_finished(table) == false)
		{
			if (is_dead(table->philos + i) == true)
			{
				write_bool(&table->table_mutex_safe, &table->end, true);
				print_doing(DIED, table->philos + i);
			}
			i++;
		}
	}
	return (NULL);
}
