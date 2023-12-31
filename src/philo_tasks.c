/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tasks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:05:47 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/17 15:29:56 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

int	mysleep(t_sim *sim, int i)
{
	int	start;
	int	time;

	start = time_since_start(sim);
	time = time_since_start(sim);
	if (!print_line(sim, i, "is sleeping"))
		return (0);
	while (time - start < sim->time_to_sleep)
	{
		time = time_since_start(sim);
		if (sim->philos[i].death_timer - (time - start) <= 0)
			set_sim_dead(sim, i);
		usleep(MS);
	}
	sim->philos[i].death_timer -= sim->time_to_sleep;
	return (1);
}

int	eat(t_sim *sim, int i, int l)
{
	int	start;
	int	time;

	check_fork(sim, l, i, 1);
	if (!print_line(sim, i, "is eating"))
		return (0);
	sim->philos[i].death_timer = sim->time_to_die;
	start = time_since_start(sim);
	time = time_since_start(sim);
	while (time - start < sim->time_to_eat)
	{
		time = time_since_start(sim);
		if (sim->philos[i].death_timer - (time - start) <= 0)
			set_sim_dead(sim, i);
		usleep(MS);
	}
	release_forks(sim, l, i);
	sim->philos[i].death_timer -= (sim->time_to_eat);
	return (1);
}
