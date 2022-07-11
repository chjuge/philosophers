/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 21:37:21 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/11 14:26:38 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	death_check(t_philo *tmp, t_state *st)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&(st->meal_check));
	// pthread_mutex_lock(&(st->writing));
	pthread_mutex_lock(&(st->peace_death));
	if (get_time_diff(get_time(), tmp->last_meal) > st->t_t_death)
	{
		print_action(tmp, st, "died");
		st->deadinside = 1;
		res = 1;
	}
	pthread_mutex_unlock(&(st->peace_death));
	pthread_mutex_unlock(&(st->meal_check));
	// pthread_mutex_unlock(&(st->writing));
	return (res);
}

int	all_ate_check(int min_meals, t_state *st)
{
	// pthread_mutex_lock(&(st->peace_death));
	pthread_mutex_lock(&(st->writing));
	printf("\n**** min meals  = %d\n", min_meals);
	pthread_mutex_unlock(&(st->writing));
	if (min_meals >= st->meals_cnt)
		st->all_ate = 1;
	// pthread_mutex_unlock(&(st->peace_death));
	return (st->all_ate);
}

void	*life_checker(void *state)
{
	int		min_meals;
	int		i;
	t_philo	*tmp;
	t_state *st;

	st = (t_state *)state;
	min_meals = 0;
	while (min_meals < st->meals_cnt)
	{
		ft_usleep(400);
		i = 0;
		min_meals = st->philo->zhralraz;
		tmp = st->philo;
		while (i++ < st->num_philo)
		{
			if (death_check(tmp, st))
			{
				// pthread_mutex_lock(&(st->writing));
				// printf("\n****** someone died\n");
				// pthread_mutex_unlock(&(st->writing));
				return (NULL);
			}
			if (min_meals > tmp->zhralraz)
				min_meals = tmp->zhralraz;
			tmp = tmp->next;
		}
		if (all_ate_check(min_meals, st))
		{
			// pthread_mutex_lock(&(st->writing));
			// printf("\n****** svse poeli\n");
			// pthread_mutex_unlock(&(st->writing));
			// pthread_exit(NULL);
			return (NULL);
		}
		// ft_usleep(200);
	}
	return (NULL);
}

void philo_eats(t_philo *ph)
{
	t_state	*st;

	st = ph->state;
	if (ph->state->num_philo < 2)
		return ;
	pthread_mutex_lock(ph->right_fork);
	print_action(ph, st, "has taken a fork");
	pthread_mutex_lock(ph->left_fork);
	print_action(ph, st, "has taken a fork");
	pthread_mutex_lock(&(st->meal_check));
	ph->last_meal = get_time();
	ph->zhralraz += 1;
	pthread_mutex_unlock(&(st->meal_check));
	print_action(ph, st, "is eating");
	ft_usleep(st->t_t_eat);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(ph->left_fork);
}

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

void	*activity(void *philo)
{
	t_philo	*ph;
	// t_state	*st;

	ph = (t_philo *)philo;
	// st = ph->state;
	while (1)
	// while (ph->zhralraz < ph->state->meals_cnt)
	{
		if (check_peace_death(ph->state))
		// if (ph->state->all_ate == 1 || ph->state->deadinside)
			// pthread_exit(NULL);
			return (NULL);
		philo_eats(ph);
		if (check_peace_death(ph->state))
		// if (ph->state->all_ate == 1 || ph->state->deadinside)
			// pthread_exit(NULL);	
			return (NULL);
		print_action(ph, ph->state, "is sleeping");
		ft_usleep(ph->state->t_t_sleep);
		// if (ph->state->all_ate == 1 || ph->state->deadinside)
		if (check_peace_death(ph->state))
			// pthread_exit(NULL);
			return (NULL);
		print_action(ph, ph->state, "is thinking");
	}
	// pthread_exit(NULL);
	return (NULL);
}

void	even(t_philo *head, t_philo *ph)
{
	while (ph->next->next != head)
	{
		ph = ph->next->next;
		pthread_create(&(ph->thread), NULL, activity, (void *)ph);
	}
	ft_usleep(10);
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
	ft_usleep(10);
	ph = head->next;
	pthread_create(&(ph->thread), NULL, activity, (void *)ph);
	while (ph->next->next->next != head->next)
	{
		ph = ph->next->next;
		pthread_create(&(ph->thread), NULL, activity, (void *)ph);
	}
	ft_usleep(10);
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
	i = 0;
	pthread_join(st->life, NULL);
	while (i++ < st->num_philo)
	{
		pthread_join(ph->thread, NULL);
		ph = ph->next;
	}
	// ft_usleep(100);
	// destroy_mutexes(st);
	// free_forks(st->forks);
	// free_philos(st->philo);
}

void	init_simulation(t_state *st)
{
	t_philo	*ph;
	// int		num;

	ph = st->philo;
	// num = 0;
	st->first_tmst = get_time();
	// while (num++ < st->num_philo)
	// {
	// 	ph->last_meal = st->first_tmst;
	// 	if (num % 2 != 1)
	// 		ft_usleep(300);
	// 	pthread_create(&(ph->thread), NULL, activity, (void *)ph);
	// 	// pthread_detach(ph->thread);
	// 	ph = ph->next;

	// }
	pthread_create(&(ph->thread), NULL, activity, (void *)ph);
	ph->last_meal = st->first_tmst;
	if (st->num_philo % 2 == 0)
		even(st->philo, ph);
	else
		odd(st->philo, ph);
	pthread_create(&(st->life), NULL, life_checker, (void *)st);
	// ft_usleep(1600);
	finish_simulation(st);
	// pthread_join(st->life, NULL);
}
