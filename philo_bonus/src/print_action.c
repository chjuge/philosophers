/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:17:15 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/13 14:22:39 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	print_action(t_philo *ph, t_state *st, char *str)
{
	if (ph->dead == 1)
		return ;
	sem_wait(st->writing);
	printf("%d ", get_time() - st->first_tmst);
	printf("%d %s\n", ph->x, str);
	sem_post(st->writing);
}
