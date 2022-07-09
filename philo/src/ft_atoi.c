/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:15:33 by mproveme          #+#    #+#             */
/*   Updated: 2022/07/08 23:07:40 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

static int	skip_spaces(const char *str)
{
	int		i;
	int		j;
	char	sp[6];

	sp[0] = '\f';
	sp[1] = '\n';
	sp[2] = '\r';
	sp[3] = '\t';
	sp[4] = '\v';
	sp[5] = ' ';
	i = 0;
	j = 0;
	while (i < 6)
	{
		if (sp[i] == str[j])
		{
			j++;
			i = 0;
			continue ;
		}
		i++;
	}
	return (j);
}

static int	sign_is(char ch)
{
	if (ch == '-')
		return (-1);
	if (ch == '+')
		return (1);
	return (0);
}

static void	check_bounds(const char *str, int *res, int count)
{
	if (str[-1] == '-')
	{
		if (ft_strncmp(str, "9223372036854775808", count) > 0)
			*res = 0;
	}
	else
	{
		if (ft_strncmp(str, "9223372036854775807", count) > 0)
			*res = -1;
	}
}

static int	get_res(const char *str, int *i, int res, int *tmp)
{
	int	count;

	count = 0;
	while (ft_isdigit(str[*i]))
	{
		if (count == 0)
			res = str[(*i)] - '0';
		else
			res = res * 10 + (str[(*i)] - '0');
		(*i)++;
		*tmp = ft_isdigit(str[(*i)]);
		count++;
	}
	if (count >= 19)
		check_bounds(str + *i - count, &res, count);
	return (res);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	tmp;
	int	is_pos;

	i = skip_spaces(str);
	res = ft_isdigit(str[i]);
	is_pos = 1;
	if (res == 0)
	{
		is_pos = sign_is(str[i++]);
		if (is_pos == 0)
			return (0);
		tmp = ft_isdigit(str[i]);
		if (!tmp)
			return (0);
		res = get_res(str, &i, res, &tmp);
	}
	else
	{
		tmp = res;
		res = get_res(str, &i, res, &tmp);
	}
	return (res * is_pos);
}
