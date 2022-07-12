/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 13:35:51 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/12 13:37:27 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	check_peace_death(t_state *st)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&(st->peace_death));
	if (st->deadinside || st->all_ate)
		res = 1;
	pthread_mutex_unlock(&(st->peace_death));
	return (res);
}

int	all_ate_check(int min_meals, t_state *st)
{
	if (min_meals >= st->meals_cnt)
		st->all_ate = 1;
	return (st->all_ate);
}

int	death_check(t_philo *tmp, t_state *st)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&(st->meal_check));
	pthread_mutex_lock(&(st->peace_death));
	if ((get_time() - tmp->last_meal) > st->t_t_death)
		res = 1;
	pthread_mutex_unlock(&(st->peace_death));
	pthread_mutex_unlock(&(st->meal_check));
	return (res);
}
