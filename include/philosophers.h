/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:34:00 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/04 15:21:14 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include<limits.h>
# include<stdbool.h>
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
	int			phil_id;
	int			death_timer;
	int			number_of_meals;
	pthread_t	thread;
}					t_philosopher;

/**
 * has info on one fork
 *	 => id number of the fork
 *	 => lock status of fork
*/
typedef struct fork {
	int				fork_id;
	bool			picked;
	pthread_mutex_t	lock;
}					t_fork;

/**
 * has all the required info for the simulation
 *	 => list of philosophers
 *	 => all variables are pretty self explanatory
 *	 => if all philos eat as many times as n_o_t_e_p_m_e, program
 *		may quit successfully
*/
typedef struct simulation_info {
	t_philosopher	*philos;
	t_fork			*forks;
	int				index;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}					t_sim;

//functions:
void	print_exit(int n);
void	free_sim(t_sim *sim);
void	set(t_sim *sim);

//check_args:
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		check_string(char *s);
int		check_args(char **argv);
t_sim	*check(int argc, char **argv);

//atoi:
int		ft_atoi(const char *s);

//run_sim:
void	run_sim(t_sim *sim);
// printf("%d, %d, %d, %d, %d\n", sim->number_of_philosophers, sim->time_to_die, sim->time_to_eat, sim->time_to_sleep, sim->number_of_times_each_philosopher_must_eat);

#endif