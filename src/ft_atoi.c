/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:32:59 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/01 14:11:57 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

static int	ft_isspace(int s)
{
	if (s == 32 || (s >= 9 && s <= 13))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *s)
{
	int		index;
	long	number;
	int		j;

	j = -1;
	index = 0;
	number = 0;
	while (ft_isspace((int) s[index]))
		index++;
	if (s[index] == '-' || s[index] == '+')
		j = index++;
	while (ft_isdigit(s[index]))
	{
		number *= 10;
		number += (((int) s[index]) - 48);
		index++;
	}
	if (j > -1 && s[j] == '-')
		number *= -1;
	if (number > INT_MAX || number < INT_MIN)
		return (-1);
	return (number);
}
