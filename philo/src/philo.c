/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:33:24 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/09 10:44:59 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	init_mutexes(t_state *st)
{
	pthread_mutex_init(&(st->meal_check), NULL);
	pthread_mutex_init(&(st->writing), NULL);
	st->forks = NULL;
	fill_forks(&(st->forks), st->num_philo);
}

int	init_state(int argc, char **argv, t_state *st)
{
	st->num_philo = ft_atoi(argv[1]);
	st->t_t_death = ft_atoi(argv[2]);
	st->t_t_eat = ft_atoi(argv[3]);
	st->t_t_sleep = ft_atoi(argv[4]);
	if (st->num_philo < 1 || st->t_t_death < 1 || st->t_t_eat
			|| st->t_t_sleep < 1)
		return (1);
	if (argv[5])
	{
		st->meals_cnt = ft_atoi(argv[5]);
		if (st->meals_cnt < 1)
			return (1);
	}
	init_mutexes(st);
	return (0);
}

int	main(int argc, char **argv)
{
	t_state	st;

	if (argc < 5 || argc > 6)
	{
		write(1, "wrong number of args\n", 21);
		return (1);
	}
	if (init_state(argc, argv, &st))
	{
		full_free();
		write(1, "wrong args\n", 11);
		return(1);
	}
	st.philo = NULL;
	fill_philos(&(st.philo), &(st.forks), st.num_philo);
}