/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:34:00 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/17 15:29:50 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define MS 200

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
	pthread_mutex_t	lock;
	pthread_mutex_t	index_lock;
	pthread_mutex_t	print_lock;
	int				index;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				is_dead;
	int				start;
}					t_sim;

//functions:
void	print_exit(int n);
void	free_sim(t_sim *sim);
void	set(t_sim *sim);

//sim utilities:
int		print_line(t_sim *sim, int i, char *str);
int		check_sim_dead(t_sim *sim, int i);
void	set_sim_dead(t_sim *sim, int i);

//forks:
int		set_forks(t_sim *sim, int l, int i);
void	check_fork(t_sim *sim, int l, int i, int flag);
void	release_forks(t_sim *sim, int l, int i);

//check arguments:
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		check_string(char *s);
int		check_args(char **argv);
t_sim	*check(int argc, char **argv);

//philosopher tasks:
int		mysleep(t_sim *sim, int i);
int		eat(t_sim *sim, int i, int l);

//atoi:
int		ft_atoi(const char *s);

//run_sim:
int		time_since_start(t_sim *sim);
int		hungry(t_sim *sim, int i);
void	set_start_time(t_sim *sim);
void	*sayhi(t_sim *sim);
void	run_sim(t_sim *sim);

#endif