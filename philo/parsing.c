/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:53:30 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/09/08 08:44:51 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	table_set_null(t_data_table *table)
{
	table->philo_nbr = -1;
	table->time_die = -1;
	table->time_eat = -1;
	table->time_sleep = -1;
	table->limit_meals = -1;
	table->time_start = -1;
	table->size_threads_run = 0;
	table->end = false;
	table->sync_philos_threads = false;
	safe_mutex_handle(&table->table_mutex_safe, INIT);
	safe_mutex_handle(&table->write_mutex_safe, INIT);
	table->fourchettes = NULL;
	table->philos = NULL;
}

int	syntax_error(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) < 1)
			return (-1);
		i++;
	}
	return (1);
}

int	parse_table(t_data_table *table, char **av)
{
	table_set_null(table);
	if (syntax_error(av) == 1)
	{
		table->philo_nbr = ft_atoi(av[1]);
		if (table->philo_nbr > 200)
			return (-1);
		table->time_die = ft_atoi(av[2]);
		table->time_eat = ft_atoi(av[3]);
		table->time_sleep = ft_atoi(av[4]);
		if (table->time_die < 60 || table->time_eat < 60
			|| table->time_sleep < 60)
			return (-1);
		if (av[5])
			table->limit_meals = ft_atoi(av[5]);
	}
	else
		return (-1);
	return (1);
}
