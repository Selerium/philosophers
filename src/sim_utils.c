/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:39:52 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/15 15:58:10 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

void	print_line(t_sim *sim, int i, char *str)
{
	int	time;

	pthread_mutex_lock(&sim->print_lock);
	time = time_since_start(sim);
	printf("%d %d %s\n", time, i + 1, str);
	pthread_mutex_unlock(&sim->print_lock);
}

int	check_sim_dead(t_sim *sim, int i)
{
	int	val;

	val = 0;
	pthread_mutex_lock(&sim->lock);
	if (sim->is_dead)
	{
		val = 1;
		sim->philos[i].death_timer = 0;
	}
	pthread_mutex_unlock(&sim->lock);
	return (val);
}

void	set_sim_dead(t_sim *sim, int i)
{
	pthread_mutex_lock(&sim->lock);
	if (!sim->is_dead)
	{
		sim->is_dead = 1;
		print_line(sim, i, "has died");
	}
	pthread_mutex_unlock(&sim->lock);
}

int	set_forks(t_sim *sim, int l, int i)
{
	print_line(sim, i, "has taken a fork");
	sim->forks[l].picked = true;
	print_line(sim, i, "has taken a fork");
	sim->forks[i].picked = true;
	return (0);
}

void	check_fork(t_sim *sim, int l, int i)
{
	int	start;
	int	time;
	int	flag;

	flag = 1;
	start = time_since_start(sim);
	while (flag && !check_sim_dead(sim, i))
	{
		if (i + 1 == sim->number_of_philosophers)
			pthread_mutex_lock(&sim->forks[i].lock);
		pthread_mutex_lock(&sim->forks[l].lock);
		if (l != i && i + 1 != sim->number_of_philosophers)
			pthread_mutex_lock(&sim->forks[i].lock);
		time = time_since_start(sim);
		if (sim->philos[i].death_timer - (time - start) <= 0)
			set_sim_dead(sim, i);
		else if (!sim->forks[l].picked && !sim->forks[i].picked)
			flag = set_forks(sim, l, i);
		pthread_mutex_unlock(&sim->forks[l].lock);
		if (l != i)
			pthread_mutex_unlock(&sim->forks[i].lock);
		if (l == i)
			flag = 1;
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

int	mysleep(t_sim *sim, int i)
{
	int	start;
	int	time;

	start = time_since_start(sim);
	time = time_since_start(sim);
	while (time - start < sim->time_to_sleep && !check_sim_dead(sim, i))
	{
		time = time_since_start(sim);
		if (sim->philos[i].death_timer - (time - start) <= 0)
			set_sim_dead(sim, i);
		usleep(MS);
	}
	if (check_sim_dead(sim, i))
		return (0);
	return (1);
}

int	eat(t_sim *sim, int i, int l)
{
	int	start;
	int	time;

	check_fork(sim, l, i);
	if (check_sim_dead(sim, i))
		return (0);
	sim->philos[i].death_timer = sim->time_to_die;
	print_line(sim, i, "is eating");
	start = time_since_start(sim);
	time = time_since_start(sim);
	while (time - start < sim->time_to_eat && !check_sim_dead(sim, i))
	{
		usleep(MS);
		if (check_sim_dead(sim, i))
			break ;
		time = time_since_start(sim);
		if (sim->philos[i].death_timer - (time - start) <= 0)
			set_sim_dead(sim, i);
	}
	release_forks(sim, l, i);
	if (check_sim_dead(sim, i))
		return (0);
	return (1);
}
