/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:05:31 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/14 20:12:55 by jadithya         ###   ########.fr       */
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
	int				time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time - sim->start);
}

int	hungry(t_sim *sim, int i)
{
	if (sim->philos[i].number_of_meals
		< sim->number_of_times_each_philosopher_must_eat)
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

	i = sim->index;
	if (i == 0)
		l = sim->number_of_philosophers - 1;
	else
		l = i - 1;
	if (i == 0)
		set_start_time(sim);
	while (sim->philos[i].number_of_meals++
		!= sim->number_of_times_each_philosopher_must_eat)
	{
		if (!eat(sim, i, l) || !hungry(sim, i))
			break ;
		if (check_sim_dead(sim, i))
			break ;
		print_line(sim, i, "is sleeping");
		if (!mysleep(sim, i))
			break ;
		print_line(sim, i, "is thinking");
	}
	return (NULL);
}

//void	*lonely_philo(t_sim *sim)
//{
//	int	time;

//	set_start_time(sim);
//	time = time_since_start(sim);
//	print_line(sim, 0, "has taken a fork");
//	while (time < sim->time_to_die)
//		usleep(MS);
//}

void	run_sim(t_sim *sim)
{
	int	i;

	i = -1;
	//if (sim->number_of_philosophers > 1)
	//{
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
	//}
	//else
	//{
	//	pthread_create(&sim->philos[i].thread, NULL, (void *) lonely_philo,
	//		sim);
	//}
}
