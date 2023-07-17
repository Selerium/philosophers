/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:05:31 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/17 13:33:49 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

int	time_since_start(t_sim *sim)
{
	struct timeval	tv;
	int				time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time - sim->start);
}

int	hungry(t_sim *sim, int i)
{
	if (sim->philos[i].number_of_meals
		!= sim->number_of_times_each_philosopher_must_eat)
		return (1);
	return (0);
}

void	set_start_time(t_sim *sim)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	sim->start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void	*sayhi(t_sim *sim)
{
	int	i;
	int	l;

	pthread_mutex_lock(&sim->index_lock);
	i = sim->index;
	pthread_mutex_unlock(&sim->index_lock);
	if (i == 0)
		l = sim->number_of_philosophers - 1;
	else
		l = i - 1;
	while (sim->philos[i].number_of_meals++
		!= sim->number_of_times_each_philosopher_must_eat)
	{
		if (!eat(sim, i, l) || !hungry(sim, i))
			break ;
		if (!mysleep(sim, i))
			break ;
		if (!print_line(sim, i, "is thinking"))
			return (0);
		usleep(MS);
	}
	return (NULL);
}

void	run_sim(t_sim *sim)
{
	int	i;

	i = -1;
	set_start_time(sim);
	while (++i < sim->number_of_philosophers)
	{
		pthread_mutex_lock(&sim->index_lock);
		sim->index = i;
		pthread_mutex_unlock(&sim->index_lock);
		pthread_create(&sim->philos[i].thread, NULL, (void *) sayhi,
			sim);
		usleep(50);
	}
	i = -1;
	while (++i < sim->number_of_philosophers)
		pthread_join(sim->philos[i].thread, NULL);
}
