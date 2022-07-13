/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 13:16:38 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/13 14:23:39 by mproveme         ###   ########.fr       */
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
		ph->id = fork();
		if (ph->id == 0)
		{
			if (num % 2 == 1)
				usleep(500);
			ph->last_meal = get_time();
			activity((void *)ph);
		}
		ph = ph->next;
		num++;
	}
}

static void	destroy_semaphors(t_state *st)
{
	sem_close(st->meal_check);
	sem_close(st->writing);
	sem_close(st->forks);
	sem_unlink("write");
	sem_unlink("eat");
	sem_unlink("forks");
}

void	finish_simulation(t_state *st)
{
	int		num;
	int		res;
	t_philo	*ph;

	num = 0;
	while (num < st->num_philo)
	{
		waitpid(-1, &res, 0);
		if (res != 0)
		{
			ph = st->philo;
			num = 0;
			while (num < st->num_philo)
			{
				kill(ph->id, SIGKILL);
				ph = ph->next;
				num++;
			}
			break ;
		}
		num++;
	}
	destroy_semaphors(st);
	free_philos(st->philo, st->num_philo);
}
