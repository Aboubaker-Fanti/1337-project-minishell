/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 20:35:45 by afanti            #+#    #+#             */
/*   Updated: 2023/06/12 19:13:58 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strchh(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (0);
		i++;
	}
	return (1);
}

char	*before_plus(char *str)
{
	int		i;
	int		s;
	char	*st;

	s = 0;
	i = ft_strlen(str);
	while (str[i] != '+')
		i--;
	st = malloc(sizeof(char) * i);
	while (str[s] && s < i)
	{
		st[s] = str[s];
		s++;
	}
	st[s] = '\0';
	return (st);
}

int	add_export(char *str, t_main **data, int d)
{
	char	*st;
	char	*s;

	st = malloc(sizeof(char) * ft_strlen(str) + 1);
	s = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[d] != '+')
	{
		st[d] = str[d];
		s[d] = str[d];
		d++;
	}
	st[d] = '\0';
	s[d] = '=';
	s[++d] = '\0';
	if (check_if_cmp(st, data, str, 1) == 0)
		return (free(s), free(st), 0);
	else if (check_if_cmp(s, data, str, 2) == 0)
		return (free(st), free(s), 0);
	else
	{
		ft_lstadd_back(data, add_node(get_line(s, d),
				ft_strch(str, '=')), 1);
		return (free(st), free(s), 0);
	}
	return (1);
}

int	add_or_creat(char *str, t_main **data)
{
	int		i;
	int		d;

	i = 0;
	d = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (str[i - 1] == '+')
			{
				if (add_export(str, data, d) == 0)
					return (0);
			}
		}
		i++;
	}
	return (1);
}

int	here_execute_else(char *str, t_main **data, char *s, char *st)
{
	int	i;

	i = 0;
	while (str[i] != '=')
	{
		st[i] = str[i];
		s[i] = str[i];
		i++;
	}
	st[i] = '\0';
	s[i] = '=';
	s[++i] = '\0';
	if (check_if_cmp(st, data, str, 0) == 0)
		return (free(s), free(st), 0);
	if (check_if_cmp(s, data, str, 0) == 0)
		return (free(s), free(st), 0);
	return (1);
}
