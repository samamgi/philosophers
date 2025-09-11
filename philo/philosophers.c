/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:37:42 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/09/08 09:19:25 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ./philo 5 800 200 200 [5]

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data_table	table;

	if (ac != 5 && ac != 6)
		exit_error("error_args");
	if (parse_table(&table, av) == -1)
		exit_error("error_syntax");
	table_init(&table);
	init_start(&table);
	clear_all(&table);
	return (0);
}
