/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 21:37:21 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/09 21:22:32 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	death_check(t_philo *tmp, t_state *st)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&(st->meal_check));
	// pthread_mutex_lock(st->meal_check);
	if (get_time_diff(get_time(), tmp->last_meal) > st->t_t_death)
	{
		pthread_mutex_lock(&(st->peace_death));
		print_action(tmp, st, "died");
		st->deadinside = 1;
		pthread_mutex_unlock(&(st->peace_death));
		res = 1;
	}
	pthread_mutex_unlock(&(st->meal_check));
	// pthread_mutex_unlock(st->meal_check);
	return (res);
}

int	all_ate_check(int min_meals, t_state *st)
{
	pthread_mutex_lock(&(st->peace_death));
	if (min_meals >= st->meals_cnt)
		st->all_ate = 1;
	pthread_mutex_unlock(&(st->peace_death));
	return (st->all_ate);
}

void	*life_checker(void *state)
{
	int		min_meals;
	int		i;
	t_philo	*tmp;
	t_state *st;

	st = (t_state *)state;
	while (1)
	{
		ft_usleep(100);
		i = 1;
		tmp = st->philo;
		min_meals = 0;
		while (i++ <= st->num_philo)
		{
			if (death_check(tmp, st))
				pthread_exit(NULL) ;
			if (min_meals > tmp->zhralraz)
				min_meals = tmp->zhralraz;
		}
		if (all_ate_check(min_meals, st))
			pthread_exit(NULL);
	}
}

void philo_eats(t_philo *ph)
{
	t_state	*st;

	st = ph->state;
	pthread_mutex_lock(ph->left_fork);
	print_action(ph, st, "has taken a fork");
	pthread_mutex_lock(ph->right_fork);
	print_action(ph, st, "has taken a fork");
	pthread_mutex_lock(&(st->meal_check));
	print_action(ph, st, "is eating");
	ph->last_meal = get_time();
	pthread_mutex_unlock(&(st->meal_check));
	ft_usleep(st->t_t_eat);
	ph->zhralraz += 1;
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
}

int	check_peace_death(t_state *st)
{
	int	res;

	res = 0;
	if (st->deadinside || st->all_ate)
		res = 1;
	return (res);
}

void	*activity(void *philo)
{
	t_philo	*ph;
	t_state	*st;

	ph = (t_philo *)philo;
	st = ph->state;
	while (1)
	{
		if (check_peace_death(st))
			break ;
		philo_eats(ph);
		if (check_peace_death(st))
			break ;
		print_action(ph, ph->state, "is sleeping");
		ft_usleep(ph->state->t_t_sleep);
		if (check_peace_death(st))
			break ;
		print_action(ph, ph->state, "is thinking");
	}
	pthread_exit(NULL);
}

void	even(t_philo *head, t_philo *ph)
{
	while (ph->next->next != head)
	{
		ph = ph->next->next;
		pthread_create(&(ph->thread), NULL, activity, (void *)ph);
	}
	ft_usleep(100);
	ph = head->next;
	pthread_create(&(ph->thread), NULL, activity, (void *)ph);
	while (ph->next->next != head->next)
	{
		ph = ph->next->next;
		pthread_create(&(ph->thread), NULL, activity, (void *)ph);
	}
}

void	odd(t_philo *head, t_philo *ph)
{
	while (ph->next->next->next != head)
	{
		ph = ph->next->next;
		pthread_create(&(ph->thread), NULL, activity, (void *)ph);
	}
	ft_usleep(100);
	ph = head->next;
	pthread_create(&(ph->thread), NULL, activity, (void *)ph);
	while (ph->next->next->next != head->next)
	{
		ph = ph->next->next;
		pthread_create(&(ph->thread), NULL, activity, (void *)ph);
	}
	ft_usleep(100);
	ph = head->prev;
	pthread_create(&(ph->thread), NULL, activity, (void *)ph);
}

void	destroy_mutexes(t_state *st)
{
	int	i;
	t_fork	*f;

	pthread_mutex_destroy(&(st->meal_check));
	pthread_mutex_destroy(&(st->peace_death));
	pthread_mutex_destroy(&(st->writing));
	i = 0;
	f = st->forks;
	while (i++ < st->num_philo)
	{
		pthread_mutex_destroy(&(f->fork));
		f = f->next;
	}
}

void	free_philos(t_philo *head)
{
	t_philo	*curr;
	t_philo	*prev;

	curr = head;
	while (curr)
	{
		prev = curr;
		curr = curr->next;
		free(prev);
	}
}

void	free_forks(t_fork *head)
{
	t_fork	*curr;
	t_fork	*prev;

	curr = head;
	while (curr)
	{
		prev = curr;
		curr = curr->next;
		free(prev);
	}
}

void	finish_simulation(t_state *st)
{
	int	i;
	t_philo	*ph;

	ph = st->philo;
	pthread_join(st->life, NULL);
	i = 0;
	while (i++ < st->num_philo)
	{
		pthread_join(ph->thread, NULL);
		ph = ph->next;
	}
	destroy_mutexes(st);
	free_philos(st->philo);
	free_forks(st->forks);
}

void	init_simulation(t_state *st)
{
	t_philo	*ph;
	int		num;

	ph = st->philo;
	num = st->num_philo;
	st->first_tmst = get_time();
	pthread_create(&(ph->thread), NULL, activity, (void *)ph);
	if (num > 1)
	{
		if (num % 2 == 0)
			even(st->philo, ph);
		else
			odd(st->philo, ph);
	}
	pthread_create(&(st->life), NULL, life_checker, (void *)st);
	finish_simulation(st);
}
