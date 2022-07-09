/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 10:40:00 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/09 21:07:44 by mproveme         ###   ########.fr       */
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
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	struct s_philo	*next;
	struct s_philo	*prev;
	int				x;
	int				last_meal;
	int				zhralraz;
	struct s_state	*state;
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t	fork;
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

int		ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t len);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);
int		get_time (void);
int		get_time_diff(int now, int before);
void	ft_usleep(int ms);
void	fill_forks(t_fork **head, int num);
void	fill_philos(t_philo **philo_h, int num, t_state *st);
void	print_action(t_philo *ph, t_state *st, char *str);
void	init_simulation(t_state *st);
#endif