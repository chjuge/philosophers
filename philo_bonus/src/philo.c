/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:33:24 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/12 20:56:24 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

// static void	init_mutexes(t_state *st)
// {
// 	pthread_mutex_init(&(st->meal_check), NULL);
// 	pthread_mutex_init(&(st->writing), NULL);
// 	st->forks = NULL;
// 	fill_forks(&(st->forks), st->num_philo);
// }

static void	init_semaphores(t_state *st)
{
	sem_unlink("write");
	sem_unlink("eat");
	sem_unlink("forks");
	st->meal_check = sem_open("eat", O_CREAT, 0644, 1);
	st->writing = sem_open("write", O_CREAT, 0644, 1);
	st->forks = sem_open("forks", O_CREAT, 0644, st->num_philo);
}

static int	init_state(char **argv, t_state *st)
{
	st->num_philo = ft_atoi(argv[1]);
	st->t_t_death = ft_atoi(argv[2]);
	st->t_t_eat = ft_atoi(argv[3]);
	st->t_t_sleep = ft_atoi(argv[4]);
	// st->all_ate = 0;
	// st->deadinside = 0;
	if (st->num_philo < 1 || st->t_t_death < 1 || st->t_t_eat < 1
		|| st->t_t_sleep < 1)
	{
		return (1);
	}
	if (argv[5])
	{
		st->meals_cnt = ft_atoi(argv[5]);
		if (st->meals_cnt < 1)
			return (1);
	}
	else
		st->meals_cnt = -1;
	// init_mutexes(st);
	init_semaphores(st);
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
	if (init_state(argv, &st))
	{
		write(1, "wrong args\n", 11);
		return (1);
	}
	st.philo = NULL;
	fill_philos(&(st.philo), st.num_philo, &st);
	init_simulation(&st);
	finish_simulation(&st);
}
