/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 13:35:51 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/12 15:23:53 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	all_ate_check(int min_meals, t_state *st)
{
	if (st->meals_cnt <= 0)
		return (0);
	if (min_meals >= st->meals_cnt)
		st->all_ate = 1;
	return (st->all_ate);
}

int	death_check(t_philo *tmp, t_state *st)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&(st->meal_check));
	if ((get_time() - tmp->last_meal) > st->t_t_death)
		res = 1;
	pthread_mutex_unlock(&(st->meal_check));
	return (res);
}
