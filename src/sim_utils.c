/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:39:52 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/14 13:19:10 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

// void	print_line(t_sim *sim, int i, char *str)
// {
// 	printf("test");
// }

void	check_fork(t_sim *sim, int l, int i)
{
	int	start;
	int	time;
	int	flag;

	flag = 1;
	start = time_since_start(sim);
	while (flag && !sim->is_dead)
	{
		pthread_mutex_lock(&sim->forks[l].lock);
		if (!sim->forks[l].picked)
		{
			time = time_since_start(sim);
			if (sim->philos[i].death_timer - (time - start) <= 0)
			{
				sim->is_dead = 1;
				start = time_since_start(sim);
				printf("%d %d has died\n", start, i + 1);
			}
			else
			{
				pthread_mutex_lock(&sim->forks[i].lock);
				if (!sim->forks[i].picked)
				{
					time = time_since_start(sim);
					if (sim->philos[i].death_timer - (time - start) <= 0)
					{
						sim->is_dead = 1;
						start = time_since_start(sim);
						printf("%d %d has died\n", start, i + 1);
					}
					else
					{
						printf("%d %d has taken a fork\n", time, i + 1);
						sim->forks[l].picked = true;
						printf("%d %d has taken a fork\n", time, i + 1);
						sim->forks[i].picked = true;
					}
					flag = 0;
				}
				pthread_mutex_unlock(&sim->forks[i].lock);
			}
		}
		pthread_mutex_unlock(&sim->forks[l].lock);
		if (flag)
			usleep(MS);
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
	time = 0;
	while (time - start <= sim->time_to_sleep && !sim->is_dead)
	{
		usleep(MS);
		if (sim->is_dead)
			break ;
		time = time_since_start(sim);
		if (sim->philos[i].death_timer - (time - start) <= 0)
		{
			sim->is_dead = 1;
			start = time_since_start(sim);
			printf("%d %d has died\n", start, i + 1);
		}
	}
	if (sim->is_dead)
		return (0);
	return (1);
}
int	eat(t_sim *sim, int i, int l)
{
	int	start;
	int	time;

	check_fork(sim, l, i);
	if (sim->is_dead)
		return (0);
	sim->philos[i].death_timer = sim->time_to_die;
	start = time_since_start(sim);
	printf("%d %d is eating\n", start, i + 1);
	time = time_since_start(sim);
	while (time - start <= sim->time_to_eat && !sim->is_dead)
	{
		usleep(MS);
		if (sim->is_dead)
			break ;
		time = time_since_start(sim);
		if (sim->philos[i].death_timer - (time - start) <= 0)
		{
			sim->is_dead = 1;
			start = time_since_start(sim);
			printf("%d %d has died\n", start, i + 1);
		}
	}
	release_forks(sim, l, i);
	if (sim->is_dead)
		return (0);
	return (1);
}
