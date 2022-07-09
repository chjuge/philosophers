/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 10:40:00 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/09 17:42:07 by mproveme         ###   ########.fr       */
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
typedef struct s_philo
{
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	pthread_t		thread;
	t_philo			*next;
	t_philo			*prev;
	int				x;
	int				last_meal;
	int				zhralraz;
	int				must_die;
	int				dead;
	t_state			*state;
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	t_fork			*next;
	t_fork			*prev;
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
	// pthread_mutex_t		death_check;
	pthread_mutex_t		writing;
	t_fork				*forks;
	t_philo				*philo;
}	t_state;


int		ft_atoi(const char *str);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);
int		get_time (void);
int		get_time_diff(int now, int before);
void	ft_usleep(int ms);
void	fill_forks(t_fork **head, int num);
void	fill_philos(t_philo **philo_h, int num, t_state *st);
void	init_simulation(t_state *st);
#endif