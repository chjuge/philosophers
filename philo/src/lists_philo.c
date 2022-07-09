/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:02:53 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/09 17:42:40 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

t_philo	*philo_init(t_fork *fork, int num, t_state *st)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->x = num;
	philo->next = NULL;
	philo->prev = NULL;
	philo->thread = NULL;
	philo->left_fork = fork->fork;
	philo->right_fork = fork->next->fork;
	philo->last_meal = 0;
	philo->dead = 0;
	philo->must_die = 0;
	philo->state = st;
	philo->zhralraz = 0;
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
	t_philo	*h;
	t_fork	*tmpf;

	tmpf = st->forks;
	i = 1;
	if (!(*philo_h))
	{
		tmp = philo_init(tmpf, i++, st);
		*philo_h = tmp;
		tmp->next = tmp;
		tmp->prev = tmp;
	}
	h = *philo_h;
	while (i <= num)
	{
		tmp = philo_init(tmpf, i, st);
		add_back_philo(philo_h, tmp);
		i++;
		tmpf = tmpf->next;
	}
}
