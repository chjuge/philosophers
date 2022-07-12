/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:17:15 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/12 13:51:32 by mproveme         ###   ########.fr       */
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
