/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 21:37:21 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/11 16:53:39 by mproveme         ###   ########.fr       */
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
		res = 1;
	pthread_mutex_unlock(&(st->peace_death));
	pthread_mutex_unlock(&(st->meal_check));
	// pthread_mutex_unlock(&(st->writing));
	return (res);
}

int	all_ate_check(int min_meals, t_state *st)
{
	pthread_mutex_lock(&(st->writing));
	printf("\n**** min meals  = %d\n", min_meals);
	pthread_mutex_unlock(&(st->writing));
	if (min_meals >= st->meals_cnt)
		st->all_ate = 1;
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
		ft_usleep(10);
		i = 0;
		min_meals = st->philo->zhralraz;
		tmp = st->philo;
		while (i++ < st->num_philo)
		{
			if (death_check(tmp, st))
			{
				print_action(tmp, st, "died");
				st->deadinside = 1;
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
			// printf("\n****** vse poeli\n");
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
	// printf("upal\n");
	// 	printf("upal\n");
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

void	free_philos(t_philo *head, int num)
{
	t_philo	*tmp;
	t_philo	*tmp_n;
	int		i;

	tmp = head;
	i = 0;
	while (i < num)
	{
		tmp_n = tmp->next;
		free(tmp);
		tmp = tmp_n;
		i++;
	}
}

void	free_forks(t_fork *head, int num)
{
	t_fork	*tmp;
	t_fork	*tmp_n;
	int		i;

	tmp = head;
	i = 0;
	while (i < num)
	{
		tmp_n = tmp->next;
		free(tmp);
		tmp = tmp_n;
		i++;
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
	destroy_mutexes(st);
	free_forks(st->forks, st->num_philo);
	free_philos(st->philo, st->num_philo);
}

void	init_simulation(t_state *st)
{
	t_philo	*ph;
	int		num;

	// printf("upal\n");
	ph = st->philo;
	num = 0;
	st->first_tmst = get_time();
	while (num < st->num_philo)
	{
		ph->last_meal = st->first_tmst;
		if (num % 2 == 1)
			ft_usleep(10);
		pthread_create(&(ph->thread), NULL, activity, (void *)ph);
		pthread_detach(ph->thread);
		ph = ph->next;
		num++;
	}
	// pthread_create(&(ph->thread), NULL, activity, (void *)ph);
	// ph->last_meal = st->first_tmst;
	// if (st->num_philo % 2 == 0)
	// 	even(st->philo, ph);
	// else
	// 	odd(st->philo, ph);
	// printf("upal\n");
	pthread_create(&(st->life), NULL, life_checker, (void *)st);
	// ft_usleep(1600);
	finish_simulation(st);
	// pthread_join(st->life, NULL);
}
