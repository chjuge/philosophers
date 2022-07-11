/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:02:53 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/11 15:52:11 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	min_max(t_fork **min, t_fork **max, t_fork *base)
{
	// min = 0;
	// max = 0;
	if (base->id < base->next->id)
	{
		*min = base;
		*max = base->next;
	}
	else
	{
		*min = base->next;
		*max = base;
	}
	// if (!min || !max)
	// 	return ;
	// printf("min: %d, max : %d\n", min->id, max->id);
}

t_philo	*philo_init(t_fork *fork, int num, t_state *st)
{
	t_philo	*philo;
	t_fork	*max;
	t_fork	*min;

	min = NULL;
	max = NULL;
	min_max(&min, &max, fork);
	philo = malloc(sizeof(t_philo));
	philo->x = num;
	philo->next = NULL;
	philo->prev = NULL;
	philo->fork_min_id = &(min->fork);
	philo->fork_max_id = &(max->fork);
	// philo->fork_min_id = &(fork->fork);
	// philo->fork_max_id = &(fork->next->fork);
	philo->last_meal = 0;
	philo->state = st;
	philo->zhralraz = 0;
	philo->dead = 0;
	// printf("min: %d, max : %d\n", fork->id, fork->next->id);
	// printf("min: %d, max : %d\n", min->id, max->id);
	// printf("philo: %d, min: %d, max : %d\n", philo->x, min->id, max->id);
	return (philo);
}

void	add_back_philo(t_philo **lst, t_philo *new)
{
	t_philo	*tmp;

	tmp = *lst;
	if (!(tmp->next) && !(tmp->prev))
	{
		tmp->next = new;
		tmp->prev = new;
		new->next = tmp;
		new->prev = tmp;
		return ;
	}
	new->next = tmp;
	new->prev = tmp->prev;
	tmp->prev = new;
	tmp = new->prev;
	tmp->next = new;
}

void	fill_philos(t_philo **philo_h, int num, t_state *st)
{
	int		i;
	t_philo	*tmp;
	t_fork	*tmpf;

	tmpf = st->forks;
	i = 1;
	if (!(*philo_h))
	{
		tmp = philo_init(tmpf, i++, st);
		*philo_h = tmp;
		tmp->next = tmp;
		tmp->prev = tmp;
		tmpf = tmpf->next;
	}
	while (i <= num)
	{
		tmp = philo_init(tmpf, i, st);
		add_back_philo(philo_h, tmp);
		i++;
		tmpf = tmpf->next;
	}
}
