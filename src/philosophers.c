/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 20:05:40 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/15 14:32:07 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

void	print_exit(int n)
{
	if (n == 1)
		printf("Error in arguments. Exiting.\n");
	if (n == 2)
		printf("Malloc error. Exiting.\n");
	exit(0);
}

void	free_sim(t_sim *sim)
{
	int	i;

	i = -1;
	if (sim->philos)
		free (sim->philos);
	if (sim->forks)
	{
		while (++i < sim->number_of_philosophers)
			pthread_mutex_destroy(&sim->forks[i].lock);
		free(sim->forks);
	}
	pthread_mutex_destroy(&sim->lock);
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->index_lock);
	if (sim)
		free(sim);
}

void	set(t_sim *sim)
{
	int	i;

	sim->philos = malloc (sizeof(t_philosopher) * sim->number_of_philosophers);
	sim->forks = malloc (sizeof(t_fork) * sim->number_of_philosophers);
	if (!sim->forks || !sim->philos)
	{
		free_sim(sim);
		print_exit(2);
	}
	i = 0;
	while (i < sim->number_of_philosophers)
	{
		sim->philos[i].phil_id = i + 1;
		sim->philos[i].number_of_meals = 0;
		sim->philos[i].death_timer = sim->time_to_die;
		sim->forks[i].fork_id = i + 1;
		sim->forks[i].picked = 0;
		pthread_mutex_init(&sim->forks[i].lock, NULL);
			i++;
	}
	pthread_mutex_init(&sim->lock, NULL);
	pthread_mutex_init(&sim->print_lock, NULL);
	pthread_mutex_init(&sim->index_lock, NULL);
}

int	main(int argc, char **argv)
{
	t_sim	*sim;

	sim = check(argc, argv);
	set(sim);
	run_sim(sim);
	free_sim(sim);
	return (0);
}
