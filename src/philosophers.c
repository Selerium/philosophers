/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 20:05:40 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/01 19:24:03 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

void	print_exit(int n)
{
	if (n == 1)
		printf("Error in arguments. Exiting.");
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
}

void	set(t_sim *sim)
{
	int	i;

	sim->philos = malloc (sizeof(t_philosopher) * sim->number_of_philosophers);
	if (!sim->philos)
		free_sim(sim);
	sim->forks = malloc (sizeof(t_philosopher) * sim->number_of_philosophers);
	if (!sim->forks)
		free_sim(sim);
	i = 0;
	while (i < sim->number_of_philosophers)
	{
		sim->philos[i].philosopher_id = i;
		sim->philos[i].number_of_meals = 0;
		sim->philos[i].death_timer = 0;
		sim->forks[i].fork_id = i;
		sim->forks[i].picked = 0;
		i++;
	}
}

void	*sayhi(int *arg)
{
	printf("This is thread %d.\n", *arg);
	return (NULL);
}

void	run_sim(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->number_of_philosophers)
	{
		pthread_create(&sim->philos[i].thread, NULL, (void *) sayhi, &i);
		usleep(50);
	}
	i = -1;
	while (++i < sim->number_of_philosophers)
		pthread_join(sim->philos[i].thread, NULL);
}

int	main(int argc, char **argv)
{
	t_sim	*sim;

	sim = check(argc, argv);
	set(sim);
	run_sim(sim);
	return (0);
}
