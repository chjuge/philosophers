/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:02:53 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/08 21:33:17 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

t_fork	*fork_init(void)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	pthread_mutex_init(&fork->fork, NULL);
	fork->next = NULL;
	fork->prev = NULL;
}

void	add_back_fork(t_fork **lst, t_fork *new)
{
	t_fork	*tmp;

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

void	fill_forks(t_fork **head, int num)
{
	int		i;
	t_fork	*tmp;
	t_fork	*h;

	i = 0;
	if (!(*head))
	{
		tmp = fork_init();
		*head = tmp;
		tmp->next = tmp;
		tmp->prev = tmp;
	}
	h = *head;
	while (i < num)
	{
		tmp = fork_init();
		add_back_fork(head, tmp);
		i++;
	}
}
