/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 21:37:21 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/12 22:23:24 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

static void	philo_eats(t_philo *ph)
{
	t_state	*st;

	st = ph->state;
	sem_wait(st->forks);
	print_action(ph, st, "has taken a fork");
	sem_wait(st->forks);
	print_action(ph, st, "has taken a fork");
	sem_wait(st->meal_check);
	ph->last_meal = get_time();
	sem_post(st->meal_check);
	print_action(ph, st, "is eating");
	ft_usleep(st->t_t_eat);
	ph->zhralraz += 1;
	sem_post(st->forks);
	sem_post(st->forks);
}

void	*activity(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	pthread_create(&(ph->monitor), NULL, life_checker, philo);
	while (ph->zhralraz != ph->state->meals_cnt
		&& ph->dead != 1)
	{
		philo_eats(ph);
		print_action(ph, ph->state, "is sleeping");
		ft_usleep(ph->state->t_t_sleep);
		print_action(ph, ph->state, "is thinking");
	}
	pthread_join(ph->monitor, NULL);
	if (ph->dead)
		exit(1);
	exit(0);
}

void	*life_checker(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (ph->zhralraz != ph->state->meals_cnt)
	{
		ft_usleep(2);
		sem_wait(ph->state->meal_check);
		if ((get_time() - ph->last_meal) > ph->state->t_t_death)
		{
			print_action(ph, ph->state, "dead");
			ph->dead = 1;
			// sem_post(ph->state->meal_check);
			sem_wait(ph->state->writing);
			exit(1);
		}
		sem_post(ph->state->meal_check);
	}
	return (NULL);
}
