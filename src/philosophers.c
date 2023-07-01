/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 20:05:40 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/01 15:52:39 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

void	print_exit(int n)
{
	if (n == 1)
		printf("Error in arguments. Exiting.");
	exit(0);
}

int	main(int argc, char **argv)
{
	t_sim	*sim;

	check(argc, argv, sim);
	return (0);
}
