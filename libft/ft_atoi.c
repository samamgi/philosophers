/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <ssadi-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 01:19:39 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/09/07 10:11:52 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		result;
	int		digit;

	if (!nptr || !*nptr)
		return (-1);
	i = 0;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
	{
		i++;
	}
	if (nptr[i] == '-')
		return (-1);
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		digit = nptr[i] - 48;
		if (result > (INT_MAX - digit) / 10)
			return (-1);
		result = result * 10 + (nptr[i] - 48);
		i++;
	}
	if (nptr[i] && !(nptr[i] >= 48 && nptr[i] <= 57))
		return (-1);
	return (result);
}
