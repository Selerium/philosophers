/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:07:15 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/17 15:46:36 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

int	set_forks(t_sim *sim, int l, int i)
{
	print_line(sim, i, "has taken a fork");
	sim->forks[l].picked = true;
	if (l != i)
	{
		print_line(sim, i, "has taken a fork");
		sim->forks[i].picked = true;
	}
	else
		return (1);
	return (0);
}

void	check_fork(t_sim *sim, int l, int i, int flag)
{
	int	start;
	int	time;

	start = time_since_start(sim);
	while (flag)
	{
		if (i + 1 == sim->number_of_philosophers)
			pthread_mutex_lock(&sim->forks[i].lock);
		if (l != i)
			pthread_mutex_lock(&sim->forks[l].lock);
		if (i + 1 != sim->number_of_philosophers && l != i)
			pthread_mutex_lock(&sim->forks[i].lock);
		time = time_since_start(sim);
		if (sim->philos[i].death_timer - (time - start) <= 0)
			set_sim_dead(sim, i);
		else if (!sim->forks[l].picked && !sim->forks[i].picked)
			flag = set_forks(sim, l, i);
		pthread_mutex_unlock(&sim->forks[l].lock);
		if (l != i)
			pthread_mutex_unlock(&sim->forks[i].lock);
		if (check_sim_dead(sim, i))
			return ;
		usleep(25);
	}
}

void	release_forks(t_sim *sim, int l, int i)
{
	pthread_mutex_lock(&sim->forks[l].lock);
	sim->forks[l].picked = false;
	pthread_mutex_unlock(&sim->forks[l].lock);
	pthread_mutex_lock(&sim->forks[i].lock);
	sim->forks[i].picked = false;
	pthread_mutex_unlock(&sim->forks[i].lock);
}
