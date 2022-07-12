/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:02:53 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/12 21:41:45 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

// t_fork	*fork_init(int i)
// {
// 	t_fork	*fork;

// 	fork = malloc(sizeof(t_fork));
// 	pthread_mutex_init(&(fork->fork), NULL);
// 	fork->next = NULL;
// 	fork->prev = NULL;
// 	fork->id = i;
// 	return (fork);
// }

// void	add_back_fork(t_fork **lst, t_fork *new)
// {
// 	t_fork	*tmp;

// 	tmp = *lst;
// 	if (!(tmp->next) && !(tmp->prev))
// 	{
// 		tmp->next = new;
// 		tmp->prev = new;
// 		new->next = tmp;
// 		new->prev = tmp;
// 		return ;
// 	}
// 	new->next = tmp;
// 	new->prev = tmp->prev;
// 	tmp->prev = new;
// 	tmp = new->prev;
// 	tmp->next = new;
// }

// void	fill_forks(t_fork **head, int num)
// {
// 	int		i;
// 	t_fork	*tmp;

// 	i = 0;
// 	if (!(*head))
// 	{
// 		tmp = fork_init(i);
// 		*head = tmp;
// 		tmp->next = tmp;
// 		tmp->prev = tmp;
// 		i++;
// 	}
// 	while (i < num)
// 	{
// 		tmp = fork_init(i);
// 		add_back_fork(head, tmp);
// 		i++;
// 	}
// }

// void	free_forks(t_fork *head, int num)
// {
// 	t_fork	*tmp;
// 	t_fork	*tmp_n;
// 	int		i;

// 	tmp = head;
// 	i = 0;
// 	while (i < num)
// 	{
// 		tmp_n = tmp->next;
// 		free(tmp);
// 		tmp = tmp_n;
// 		i++;
// 	}
// }
