/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:05:31 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/01 21:38:40 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

void	*sayhi(t_sim *sim)
{
	struct timeval	tv;
	int				i;

	gettimeofday(&tv, NULL);
	i = sim->index;
	printf("%ld %d is eating\n", tv.tv_usec / 1000, i);
	usleep(sim->time_to_eat * 1000);
	gettimeofday(&tv, NULL);
	printf("%ld %d is sleeping\n", tv.tv_usec / 1000, i);
	usleep(sim->time_to_sleep * 1000);
	gettimeofday(&tv, NULL);
	printf("%ld %d is thinking\n", tv.tv_usec / 1000, i);
	return (NULL);
}

void	run_sim(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->number_of_philosophers)
	{
		sim->index = i;
		pthread_create(&sim->philos[i].thread, NULL, (void *) sayhi,
			sim);
		usleep(50);
	}
	i = -1;
	while (++i < sim->number_of_philosophers)
		pthread_join(sim->philos[i].thread, NULL);
}
