/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 10:40:00 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/12 13:39:12 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
# define PHILO
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/time.h>
typedef struct s_philo
{
	pthread_mutex_t	*fork_min_id;
	pthread_mutex_t	*fork_max_id;
	pthread_t		thread;
	struct s_philo	*next;
	struct s_philo	*prev;
	int				x;
	int				last_meal;
	int				zhralraz;
	int				dead;
	struct s_state	*state;
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
	struct s_fork	*next;
	struct s_fork	*prev;
}	t_fork;

typedef struct s_state
{
	int					num_philo;
	int					t_t_death;
	int					t_t_eat;
	int					t_t_sleep;
	int					meals_cnt;
	int					first_tmst;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		writing;
	pthread_mutex_t		peace_death;
	t_fork				*forks;
	t_philo				*philo;
	int					all_ate;
	int					deadinside;
	pthread_t			life;
}	t_state;

/* ft_atoi.c */
int		ft_atoi(const char *str);
/* ft_atoi.c */
/* ft_itoa.c */
char	*ft_itoa(int n);
/* ft_itoa.c */
/* ustils.c */
int		ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t len);
size_t	ft_strlen(const char *s);
int		get_time (void);
void	ft_usleep(int ms);
/* ustils.c */
/* lists_forks.c */
void	fill_forks(t_fork **head, int num);
void	free_forks(t_fork *head, int num);
/* lists_forks.c */
/* lists_philo.c */
void	fill_philos(t_philo **philo_h, int num, t_state *st);
void	free_philos(t_philo *head, int num);
/* lists_philo.c */
void	print_action(t_philo *ph, t_state *st, char *str);
/* simulation.c */
void	init_simulation(t_state *st);
void	finish_simulation(t_state *st);
/* simulation.c */
void	*activity(void *philo);
void	*life_checker(void *state);
/* check.c */
int	death_check(t_philo *tmp, t_state *st);
int	all_ate_check(int min_meals, t_state *st);
int	check_peace_death(t_state *st);
/* check.c */

#endif