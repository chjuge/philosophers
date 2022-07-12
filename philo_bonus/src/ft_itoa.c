/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:13:01 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/09 17:13:13 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

static int	find_count(int n)
{
	int	count;

	count = 0;
	if (n < 0)
		count++;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	get_digit(unsigned int *n)
{
	int	res;

	res = *n % 10 + '0';
	*n = *n / 10;
	return (res);
}

char	*ft_itoa(int n)
{
	int				count;
	char			*str;
	int				i;
	unsigned int	num;

	count = find_count(n);
	str = malloc(sizeof(char) * count + 1);
	if (!str)
		return (0);
	i = count;
	str[i--] = '\0';
	if (n >= 0)
		num = n;
	else
	{
		num = -n;
		count--;
		str[0] = '-';
	}
	while (count-- > 0)
		str[i--] = get_digit(&num);
	return (str);
}
