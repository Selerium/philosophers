/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 19:39:58 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/14 18:02:23 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	check_string(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (ft_isalpha(s[i]) || (s[i] == '-'
				&& (s[i + 1] == '\0' || !ft_isdigit(s[i + 1]))))
			return (0);
	return (1);
}

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (1);
		if (ft_atoi(argv[i]) <= 0)
			return (1);
	}
	return (0);
}

t_sim	*check(int argc, char **argv)
{
	t_sim	*sim;

	sim = malloc (sizeof(t_sim));
	if (!sim)
		free_sim(sim);
	if (argc < 5 || argc > 6 || check_args(argv))
		print_exit(1);
	sim->number_of_philosophers = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	sim->is_dead = 0;
	if (argc == 6)
		sim->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		sim->number_of_times_each_philosopher_must_eat = -1;
	return (sim);
}
