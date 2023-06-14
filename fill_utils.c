/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 20:29:53 by brahim            #+#    #+#             */
/*   Updated: 2023/06/13 22:33:41 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_pwd(t_main *data, char *str, int s)
{
	char	*st;
	int		i;

	i = 0;
	st = ft_calloc((ft_strlen(data->var_value) + ft_strlen(str)), 1);
	while (data->var_value[i])
	{
		if (s == 3)
			break ;
		st[i] = data->var_value[i];
		if (data->var_value[i] == '/')
			s++;
		i++;
	}
	s = 2;
	while (str[s])
		st[i++] = str[s++];
	st[i] = '\0';
	return (st);
}

void	comlite_here(char *st)
{
	write (2, "minishell: cd: ", 15);
	ft_putstr_fd(st, 2);
	write (2, " No such file or directory\n", 27);
	g_exit_state = 1;
}

void	comlite_her(char *pwd, t_main **main)
{
	char	ss[1024];

	change_old_or_new_pwd(main, pwd, 0);
	getcwd(ss, sizeof(ss));
	change_old_or_new_pwd(main, ss, 1);
}

void	if_thereis_no_env(t_main **main, char *str, int s, char *pwd)
{
	char	*st;
	int		i;
	t_main	*data;

	i = 0;
	st = NULL;
	data = *main;
	while (data)
	{
		if (ft_memcmp(data->var_name, "PWD=") == 0)
		{
			st = fill_pwd(data, str, s);
			break ;
		}
		data = data->next;
	}	
	if (chdir (st) == 0)
		comlite_her(pwd, main);
	else
		comlite_here(st);
	free(st);
}
