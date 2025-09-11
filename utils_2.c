/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:02:05 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/09/10 21:25:47 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sync_philos_threads(t_data_table *table)
{
	while (read_bool(&table->table_mutex_safe,
			&table->sync_philos_threads) == false)
		;
}

void	init_annex(t_data_table *table)
{
	if (table->philo_nbr > 1)
	{
		safe_thread_handle(&table->monitor, monitor, table, CREATE);
		table->time_start = gettime();
		write_bool(&table->table_mutex_safe, &table->sync_philos_threads, true);
	}
}

void	unsynch_philo(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(30, philo->table);
	}
	else
	{
		if (philo->id % 2 == 0)
			think(philo, true);
	}
}
