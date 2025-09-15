/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_inits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 11:43:40 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/09/08 08:16:44 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_fourchettes(t_philo *philo, t_fourchette *fourchettes, int i)
{
	int	size_philo;

	size_philo = philo->table->philo_nbr;
	philo->left_fourchette = &fourchettes[(i + 1) % size_philo];
	philo->right_fourchette = &fourchettes[i];
	if (philo->id % 2 == 0)
	{
		philo->left_fourchette = &fourchettes[i];
		philo->right_fourchette = &fourchettes[(i + 1) % size_philo];
	}
}

void	philo_init(t_data_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->meals = 0;
		philo->last_meal_time = -1;
		philo->max = false;
		philo->table = table;
		safe_mutex_handle(&philo->philo_mutex_safe, INIT);
		set_fourchettes(philo, table->fourchettes, i);
		i++;
	}
}

void	table_init(t_data_table *table)
{
	int	i;

	i = 0;
	table->fourchettes = (t_fourchette *)malloc(sizeof(t_fourchette)
			* (table->philo_nbr));
	if (!(table->fourchettes))
		return ;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * (table->philo_nbr));
	if (!(table->philos))
		return ;
	while (i < table->philo_nbr)
	{
		safe_mutex_handle(&table->fourchettes[i].fourchette, INIT);
		table->fourchettes[i].fourchette_id = i;
		i++;
	}
	philo_init(table);
}
