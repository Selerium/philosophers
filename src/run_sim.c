/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:05:31 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/04 15:52:33 by jadithya         ###   ########.fr       */
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

void	lock_forks(pthread_mutex_t *l1, pthread_mutex_t *l2, int i)
{
	struct timeval	tv;

	pthread_mutex_lock(l1);
	gettimeofday(&tv, NULL);
	printf("%ld %d has taken a fork\n", tv.tv_usec / 1000, i + 1);
	pthread_mutex_lock(l2);
	gettimeofday(&tv, NULL);
	printf("%ld %d has taken a fork\n", tv.tv_usec / 1000, i + 1);
	gettimeofday(&tv, NULL);
	printf("%ld %d is eating\n", tv.tv_usec / 1000, i + 1);
}

void	unlock_forks(pthread_mutex_t *l1, pthread_mutex_t *l2, int i)
{
	struct timeval	tv;

	pthread_mutex_unlock(l1);
	pthread_mutex_unlock(l2);
	gettimeofday(&tv, NULL);
	printf("%ld %d is sleeping\n", tv.tv_usec / 1000, i + 1);
}

void	*sayhi(t_sim *sim)
{
	struct timeval	tv;
	int				i;
	int				l;
	int				r;

	i = sim->index;
	if (i == 0)
		l = sim->number_of_philosophers - 1;
	else
		l = i - 1;
	r = i;
	while ((r || l) && sim->philos[i].number_of_meals++
		< sim->number_of_times_each_philosopher_must_eat)
	{
		lock_forks(&sim->forks[l].lock, &sim->forks[r].lock, i);
		usleep(sim->time_to_eat * 1000);
		unlock_forks(&sim->forks[l].lock, &sim->forks[r].lock, i);
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
