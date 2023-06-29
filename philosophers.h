/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:34:00 by jadithya          #+#    #+#             */
/*   Updated: 2023/06/29 21:52:37 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include<string.h>
# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<sys/time.h>
# include<pthread.h>

/**
 * has info on one philosopher
 *	 => id number of the philosopher
 *	 => timer for death; measures how long it's been since last ate
 *	 => number of meals had so far
*/
typedef struct philosopher {
	int	philosopher_id;
	int	death_timer;
	int	number_of_meals;
}					t_philosopher;

/**
 * has all the required info for the simulation
 *	 => list of philosophers
 *	 => all variables are pretty self explanatory
 *	 => if all philos eat as many times as n_o_t_e_p_m_e, program
 *		may quit successfully
*/
typedef struct simulation_info {
	t_philosopher	*list;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}					t_info;


#endif