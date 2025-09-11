/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_data_races.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 08:57:59 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/09/08 09:15:18 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	write_bool(pthread_mutex_t *mutex, bool *to_write, bool new)
{
	safe_mutex_handle(mutex, LOCK);
	*to_write = new;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	read_bool(pthread_mutex_t *mutex, bool *to_read)
{
	bool	res;

	safe_mutex_handle(mutex, LOCK);
	res = *to_read;
	safe_mutex_handle(mutex, UNLOCK);
	return (res);
}

void	write_long(pthread_mutex_t *mutex, long *to_write, long new)
{
	safe_mutex_handle(mutex, LOCK);
	*to_write = new;
	safe_mutex_handle(mutex, UNLOCK);
}

long	read_long(pthread_mutex_t *mutex, long *to_read)
{
	long	res;

	safe_mutex_handle(mutex, LOCK);
	res = *to_read;
	safe_mutex_handle(mutex, UNLOCK);
	return (res);
}

bool	is_finished(t_data_table *table)
{
	return (read_bool(&table->table_mutex_safe, &table->end));
}
