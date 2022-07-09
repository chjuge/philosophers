/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 21:37:21 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/09 17:44:26 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	print_action(t_philo *ph, t_state *st, char *str)
{
	char	*str_n;
	char	*str_tmst;

	pthread_mutex_lock(&(st->writing));
	str_n = ft_itoa(ph->x);
	str_tmst = ft_itoa(get_time() - st->first_tmst);
	write(1, str_tmst, ft_strlen(str_tmst));
	write(1, " ", 1);
	write(1, str_n, ft_strlen(str_n));
	write(1, " ", 1);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	pthread_mutex_unlock(&(st->writing));
	return ;
}

void philo_eats(t_philo *ph)
{
	t_state	*st;

	st = ph->state;
	pthread_mutex_lock(&(ph->left_fork));
	print_action(ph, st, "has taken a fork");
	pthread_mutex_lock(&(ph->right_fork));
	print_action(ph, st, "has taken a fork");
	pthread_mutex_lock(&(st->meal_check));
	print_action(ph, st, "is eating");
	ph->last_meal = get_time();
	pthread_mutex_unlock(&(st->meal_check));
	ft_usleep(st->t_t_eat);
	ph->zhralraz += 1;
	pthread_mutex_unlock(&(ph->left_fork));
	pthread_mutex_unlock(&(ph->right_fork));
}


void	activity(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		if (ph->must_die)
			return ;
		philo_eats(ph);
	}
}

void	even(t_philo *head, t_philo *ph, int num)
{
	while (ph->next->next != head)
	{
		ph = ph->next->next;
		pthread_create(ph->thread, NULL, activity, (void *)ph);
	}
	ft_usleep(100);
	ph = head->next;
	pthread_create(ph->thread, NULL, activity, (void *)ph);
	while (ph->next->next != head->next)
	{
		ph = ph->next->next;
		pthread_create(ph->thread, NULL, activity, (void *)ph);
	}
}

void	odd(t_philo *head, t_philo *ph, int num)
{
	while (ph->next->next->next != head)
	{
		ph = ph->next->next;
		pthread_create(ph->thread, NULL, activity, (void *)ph);
	}
	ft_usleep(100);
	ph = head->next;
	pthread_create(ph->thread, NULL, activity, (void *)ph);
	while (ph->next->next->next != head->next)
	{
		ph = ph->next->next;
		pthread_create(ph->thread, NULL, activity, (void *)ph);
	}
	ft_usleep(100);
	ph = head->prev;
	pthread_create(ph->thread, NULL, activity, (void *)ph);
}

void	init_simulation(t_state *st)
{
	t_philo	*ph;
	int		num;

	ph = st->philo;
	num = st->num_philo;
	st->first_tmst = get_time();
	pthread_create(ph->thread, NULL, activity, (void *)ph);
	if (num > 1)
	{
		if (num % 2 == 0)
			even(st->philo, ph, num);
		else
			odd(st->philo, ph, num);
	}
}
