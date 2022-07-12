/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 21:37:21 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/12 14:06:28 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

static void	philo_eats(t_philo *ph)
{
	t_state	*st;

	st = ph->state;
	if (ph->state->num_philo < 2)
		return ;
	pthread_mutex_lock(ph->fork_min_id);
	print_action(ph, st, "has taken a fork");
	pthread_mutex_lock(ph->fork_max_id);
	print_action(ph, st, "has taken a fork");
	pthread_mutex_lock(&(st->meal_check));
	ph->last_meal = get_time();
	ph->zhralraz += 1;
	print_action(ph, st, "is eating");
	pthread_mutex_unlock(&(st->meal_check));
	ft_usleep(st->t_t_eat);
	pthread_mutex_unlock(ph->fork_min_id);
	pthread_mutex_unlock(ph->fork_max_id);
}

void	*activity(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (death_check(ph, ph->state) != 1)
	{
		philo_eats(ph);
		print_action(ph, ph->state, "is sleeping");
		ft_usleep(ph->state->t_t_sleep);
		print_action(ph, ph->state, "is thinking");
	}
	return (NULL);
}

int	death_check_life(t_philo *tmp, t_state *st)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&(st->meal_check));
	pthread_mutex_lock(&(st->peace_death));
	if ((get_time() - tmp->last_meal) > st->t_t_death)
	{
		res = 1;
		st->deadinside = 1;
		print_action(tmp, st, "died");
	}
	pthread_mutex_unlock(&(st->peace_death));
	pthread_mutex_unlock(&(st->meal_check));
	return (res);
}

void	*life_checker(void *state)
{
	int		min_meals;
	int		i;
	t_philo	*tmp;
	t_state	*st;

	st = (t_state *)state;
	min_meals = 0;
	while (min_meals < st->meals_cnt)
	{
		ft_usleep(1);
		i = 0;
		min_meals = st->philo->zhralraz;
		tmp = st->philo;
		while (i++ < st->num_philo)
		{
			if (death_check_life(tmp, st))
				return (NULL);
			if (min_meals > tmp->zhralraz)
				min_meals = tmp->zhralraz;
			tmp = tmp->next;
		}
		if (all_ate_check(min_meals, st))
			return (NULL);
	}
	return (NULL);
}
