/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:39:52 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/15 22:09:06 by jadithya         ###   ########.fr       */
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
