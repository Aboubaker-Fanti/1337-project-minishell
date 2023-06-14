/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:42:04 by afanti            #+#    #+#             */
/*   Updated: 2023/06/13 22:37:21 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_functin_comp(t_main **main, t_main	*data, int s)
{
	while (data)
	{
		if (ft_memcmp(data->var_name, "PWD=") == 0)
		{
			while (data->var_value[s])
			{
				write ((*main)->fd_output, &data->var_value[s], 1);
				s++;
			}
			write ((*main)->fd_output, "\n", 1);
			return (0);
		}
		data = data->next;
	}
	return (1);
}

void	pwd_function(t_main **main)
{
	char	cwd[1024];
	t_main	*data;
	int		s;

	s = 0;
	data = (*main);
	if (pwd_functin_comp(main, data, s) != 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			while (cwd[s])
			{
				write ((*main)->fd_output, &cwd[s], 1);
				s++;
			}
			write ((*main)->fd_output, "\n", 1);
		}
	}
}

void	check_and_add_oldpwd(t_main **main)
{
	int		i;
	int		d;
	t_main	*data;

	data = *main;
	i = 0;
	d = 0;
	while (data)
	{
		if (ft_memcmp(data->var_name, "OLDPWD=") == 0
			|| ft_memcmp(data->var_name, "OLDPWD") == 0)
			i = 1;
		if (ft_memcmp(data->var_name, "_=") == 0)
			d = 2;
		data = data->next;
	}
	if (i != 1)
	{
		ft_lstadd_back(main, add_node(ft_strdup("OLDPWD"),
				ft_strch("OLDPWD=", '=')), 1);
	}
	if (d != 2)
		ft_lstadd_back(main, add_node(ft_strdup("_="),
				ft_strch("_=/usr/bin/env", '=')), 1);
}

int	check_if_there_duble_blus(char *str)
{
	int	i;
	int	s;

	i = 0;
	s = 0;
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-')
			s++;
		i++;
	}
	if (s >= 2)
		return (1);
	return (0);
}

void	exit_function_com(char **data, int i, int s)
{
	if (check_if_there_duble_blus(data[i]) == 1)
		print_numeric_argement(data[i]);
	else
	{
		while (data[i] && g_exit_state == 0)
		{
			while (data[i][s])
			{
				if (ft_isdigi(data[i][s]) == 0)
					g_exit_state = 255;
				s++;
			}
			if (s >= 20 || g_exit_state == 255)
				print_numeric_argement(data[i]);
			i++;
		}
		if (i == 2)
		{
			if (data[1][0] == '-' && ft_atoi(data[1]) <= -256)
				exit(256 + ft_atoi(data[1]));
			exit(ft_atoi(data[1]));
		}
	}
}
