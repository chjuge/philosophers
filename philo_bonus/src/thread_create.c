/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 21:37:21 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/12 22:07:39 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

// static void	philo_eats(t_philo *ph)
// {
// 	t_state	*st;

// 	st = ph->state;
// 	if (ph->state->num_philo < 2)
// 		return ;
// 	pthread_mutex_lock(ph->fork_min_id);
// 	print_action(ph, st, "has taken a fork");
// 	pthread_mutex_lock(ph->fork_max_id);
// 	print_action(ph, st, "has taken a fork");
// 	pthread_mutex_lock(&(st->meal_check));
// 	ph->last_meal = get_time();
// 	pthread_mutex_unlock(&(st->meal_check));
// 	print_action(ph, st, "is eating");
// 	ft_usleep(st->t_t_eat);
// 	ph->zhralraz += 1;
// 	pthread_mutex_unlock(ph->fork_min_id);
// 	pthread_mutex_unlock(ph->fork_max_id);
// }


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
		|| ph->dead != 1)
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

// static int	death_check_life(t_philo *tmp, t_state *st)
// {
// 	int	res;

// 	res = 0;
// 	pthread_mutex_lock(&(st->meal_check));
// 	if ((get_time() - tmp->last_meal) > st->t_t_death)
// 	{
// 		res = 1;
// 		st->deadinside = 1;
// 		print_action(tmp, st, "died");
// 	}
// 	pthread_mutex_unlock(&(st->meal_check));
// 	return (res);
// }

// void	*life_checker(void *state)
// {
// 	int		min_meals;
// 	int		i;
// 	t_philo	*tmp;
// 	t_state	*st;

// 	st = (t_state *)state;
// 	min_meals = 0;
// 	while (st->all_ate != 1)
// 	{
// 		ft_usleep(1);
// 		i = 0;
// 		min_meals = st->philo->zhralraz;
// 		tmp = st->philo;
// 		while (i++ < st->num_philo)
// 		{
// 			if (death_check_life(tmp, st))
// 				return (NULL);
// 			if (min_meals > tmp->zhralraz)
// 				min_meals = tmp->zhralraz;
// 			tmp = tmp->next;
// 		}
// 		if (all_ate_check(min_meals, st))
// 			return (NULL);
// 	}
// 	return (NULL);
// }

void	*life_checker(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		ft_usleep(5);
		sem_wait(ph->state->meal_check);
		if ((get_time() - ph->last_meal) > ph->state->t_t_death)
		{
			ph->dead = 1;
			print_action(ph, ph->state, "dead");
			// sem_post(ph->state->meal_check);
			// sem_wait(ph->state->writing);
			exit(1);
		}
		sem_post(ph->state->meal_check);

	}
}
