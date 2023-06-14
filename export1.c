/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 20:34:57 by afanti            #+#    #+#             */
/*   Updated: 2023/06/10 20:35:31 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	change_value_comp(t_main **main, char *st, int s, int k)
{
	char	*str;

	str = malloc(sizeof(char) * ft_strlen((*main)->var_value) + ft_strlen(st));
	str[0] = '=';
	while ((*main)->var_value[s])
	{
		str[k] = (*main)->var_value[s];
		s++;
		k++;
	}
	s = 0;
	while (st[s] != '=')
		s++;
	while (st[++s])
	{
		str[k] = st[s];
		k++;
	}
	str[k] = '\0';
	free((*main)->var_value);
	(*main)->var_value = ft_strch(str, '=');
	free(str);
}

void	change_value_all(t_main **main, char *st, int i)
{
	int		d;
	int		k;
	int		s;
	t_main	*data;

	data = *main;
	s = 0;
	k = 1;
	d = 0;
	while (*main)
	{
		if (d == i)
		{
			if ((*main)->var_value[0] == '\0')
			{
				free((*main)->var_value);
				(*main)->var_value = ft_strch(st, '=');
			}
			else if ((*main)->var_value[0] != '\0')
				change_value_comp(main, st, s, k);
		}
		d++;
		(*main) = (*main)->next;
	}
	*main = data;
}

void	change_value_ou_all_compl(t_main **main, char *str, char *st)
{
	free((*main)->var_name);
	(*main)->var_name = get_line(str, ft_strlen(str));
	free((*main)->var_value);
	(*main)->var_value = ft_strch(st, '=');
}

void	change_value_ou_all(t_main **main, char *st, int i)
{
	int		s;
	int		d;
	t_main	*data;
	char	*str;

	data = *main;
	s = 0;
	d = 0;
	str = malloc(sizeof(char) * i);
	while (st[s] != '+')
	{
		str[s] = st[s];
		s++;
	}
	str[s] = '=';
	str[++s] = '\0';
	while (*main)
	{
		if (d == i)
			change_value_ou_all_compl(main, str, st);
		d++;
		(*main) = (*main)->next;
	}
	*main = data;
	free(str);
}
