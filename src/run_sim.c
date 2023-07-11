/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:05:31 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/11 17:06:45 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

void	set_forks(t_fork *f1, t_fork *f2, t_sim *sim, int i)
{
	if (i == 0)
		f1 = &sim->forks[sim->number_of_philosophers - 1];
	else
		f1 = &sim->forks[i - 1];
	f2 = &sim->forks[i];
	f1->picked = false;
	f2->picked = false;
}

int	time_since_start(t_sim *sim)
{
	struct timeval	tv;
	int				diff;

	gettimeofday(&tv, NULL);
	diff = (tv.tv_sec * 1000 + tv.tv_usec / 1000)
		- (sim->start.tv_sec * 1000 + sim->start.tv_usec / 1000);
	return (diff);
}

void	*sayhi(t_sim *sim)
{
	int	time;
	int	i;
	int	l;
	int	r;

	i = sim->index;
	if (i == 0)
		l = sim->number_of_philosophers - 1;
	else
		l = i - 1;
	r = i;
	if (i == 0)
		gettimeofday(&sim->start, NULL);
	while (sim->philos[i].number_of_meals++
		< sim->number_of_times_each_philosopher_must_eat && (r || l))
	{
		printf("%d %d is eating\n", time, i + 1);
		printf("%d %d is sleeping\n", time, i + 1);
		printf("%d %d is thinking\n", time, i + 1);
	}
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
