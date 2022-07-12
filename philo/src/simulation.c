/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 13:16:38 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/12 15:23:43 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	init_simulation(t_state *st)
{
	t_philo	*ph;
	int		num;

	ph = st->philo;
	num = 0;
	st->first_tmst = get_time();
	while (num < st->num_philo)
	{
		ph->last_meal = st->first_tmst;
		if (num % 2 == 1)
			ft_usleep(1);
		pthread_create(&(ph->thread), NULL, activity, (void *)ph);
		pthread_detach(ph->thread);
		ph = ph->next;
		num++;
	}
	pthread_create(&(st->life), NULL, life_checker, (void *)st);
}

static void	destroy_mutexes(t_state *st)
{
	int		i;
	t_fork	*f;

	pthread_mutex_destroy(&(st->meal_check));
	pthread_mutex_destroy(&(st->writing));
	i = 0;
	f = st->forks;
	while (i++ < st->num_philo)
	{
		pthread_mutex_destroy(&(f->fork));
		f = f->next;
	}
}

void	finish_simulation(t_state *st)
{
	pthread_join(st->life, NULL);
	destroy_mutexes(st);
	free_forks(st->forks, st->num_philo);
	free_philos(st->philo, st->num_philo);
}
