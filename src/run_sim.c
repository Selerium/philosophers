/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:05:31 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/03 18:07:12 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

void	set_forks(t_fork forks[2], t_sim *sim, int i)
{
	if (i == 0)
		forks[L] = sim->forks[sim->number_of_philosophers - 1];
	else
		forks[L] = sim->forks[i - 1];
	forks[R] = sim->forks[i];
}

void	lock_forks(t_fork forks[2], int i)
{
	struct timeval	tv;

	pthread_mutex_lock(&forks[0].lock);
	gettimeofday(&tv, NULL);
	printf("%ld %d has picked up a fork\n", tv.tv_usec / 1000, i + 1);
	pthread_mutex_lock(&forks[1].lock);
	gettimeofday(&tv, NULL);
	printf("%ld %d has picked up a fork\n", tv.tv_usec / 1000, i + 1);
}

void	unlock_forks(t_fork forks[2])
{
	pthread_mutex_unlock(&forks[0].lock);
	pthread_mutex_unlock(&forks[1].lock);
}

void	*sayhi(t_sim *sim)
{
	struct timeval	tv;
	int				i;
	t_fork			forks[2];

	i = sim->index;
	set_forks(forks, sim, i);
	while (sim->philos[i].number_of_meals++
		< sim->number_of_times_each_philosopher_must_eat)
	{
		lock_forks(forks, i);
		gettimeofday(&tv, NULL);
		printf("%ld %d is eating\n", tv.tv_usec / 1000, i + 1);
		usleep(sim->time_to_eat * 1000);
		unlock_forks(forks);
		gettimeofday(&tv, NULL);
		printf("%ld %d is sleeping\n", tv.tv_usec / 1000, i + 1);
		usleep(sim->time_to_sleep * 1000);
		gettimeofday(&tv, NULL);
		printf("%ld %d is thinking\n", tv.tv_usec / 1000, i + 1);
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
