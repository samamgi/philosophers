/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 08:19:08 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/09/08 09:50:16 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*solo_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	printf("0 1 has taken a fork\n");
	ft_usleep(philo->table->time_die, philo->table);
	printf("%li 1 has died\n", philo->table->time_die);
	return (NULL);
}

void	think(t_philo *philo, bool fair)
{
	long	eat;
	long	sleep;
	long	think;

	if (fair == false)
		print_doing(THINKING, philo);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	eat = philo->table->time_eat;
	sleep = philo->table->time_sleep;
	think = eat * 2 - sleep;
	if (think < 0)
		think = 0;
	ft_usleep(think * 0.42, philo->table);
}

void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->left_fourchette->fourchette, LOCK);
	safe_mutex_handle(&philo->right_fourchette->fourchette, LOCK);
	print_doing(TAKE_LEFT_FORK, philo);
	print_doing(TAKE_RIGHT_FORK, philo);
	write_long(&philo->philo_mutex_safe, &philo->last_meal_time, gettime());
	philo->meals++;
	print_doing(EATING, philo);
	ft_usleep(philo->table->time_eat, philo->table);
	if (philo->table->limit_meals > 0
		&& philo->meals == philo->table->limit_meals)
		write_bool(&philo->philo_mutex_safe, &philo->max, true);
	safe_mutex_handle(&philo->left_fourchette->fourchette, UNLOCK);
	safe_mutex_handle(&philo->right_fourchette->fourchette, UNLOCK);
}

void	*simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	sync_philos_threads(philo->table);
	write_long(&philo->philo_mutex_safe, &philo->last_meal_time, gettime());
	add_long(&philo->table->table_mutex_safe, &philo->table->size_threads_run);
	unsynch_philo(philo);
	while (is_finished(philo->table) == false)
	{
		if (read_bool(&philo->philo_mutex_safe, &philo->max) == true)
			break ;
		eat(philo);
		print_doing(SLEEPING, philo);
		ft_usleep(philo->table->time_sleep, philo->table);
		think(philo, false);
	}
	return (NULL);
}

void	init_start(t_data_table *table)
{
	int	i;

	i = -1;
	if (table->philo_nbr == 0)
		return ;
	else if (table->philo_nbr == 1)
		safe_thread_handle(&table->philos[0].thread_philo_id, solo_philo,
			&table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_philo_id, simulation,
				&table->philos[i], CREATE);
	}
	if (table->philo_nbr > 1)
		init_annex(table);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_philo_id, NULL, NULL, JOIN);
	if (table->philo_nbr > 1)
	{
		write_bool(&table->table_mutex_safe, &table->end, true);
		safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
	}
}
