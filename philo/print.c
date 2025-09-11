/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:09:02 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/09/08 15:09:12 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_doing(t_philo_status doing, t_philo *philo)
{
	long	during;

	during = gettime() - philo->table->time_start;
	if (read_bool(&philo->philo_mutex_safe, &philo->max))
		return ;
	safe_mutex_handle(&philo->table->write_mutex_safe, LOCK);
	if ((doing == TAKE_LEFT_FORK || doing == TAKE_RIGHT_FORK)
		&& is_finished(philo->table) == false)
		printf("%-6ld %d has taken a fork\n", during, philo->id);
	if (doing == EATING && is_finished(philo->table) == false)
		printf("%-6ld %d is eating\n", during, philo->id);
	if (doing == SLEEPING && is_finished(philo->table) == false)
		printf("%-6ld %d is sleeping\n", during, philo->id);
	if (doing == THINKING && is_finished(philo->table) == false)
		printf("%-6ld %d is thinking\n", during, philo->id);
	if (doing == DIED)
		printf("%-6ld %d died\n", during, philo->id);
	safe_mutex_handle(&philo->table->write_mutex_safe, UNLOCK);
}
