/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:23:14 by afanti            #+#    #+#             */
/*   Updated: 2023/06/13 14:02:37 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chenge_old_or_new_comp(t_main **data, char *str, char *cwd, int i)
{
	if (cwd != NULL)
	{
		free((*data)->var_name);
		(*data)->var_name = get_line(str, ft_strlen(str));
		free((*data)->var_value);
		(*data)->var_value = malloc(sizeof(char) * (ft_strlen(cwd) + 1));
		while (cwd && cwd[i])
		{
			(*data)->var_value[i] = cwd[i];
			i++;
		}
		(*data)->var_value[i] = '\0';
	}
}

void	change_old_or_new_pwd(t_main **data, char *cwd, int s)
{
	t_main	*main;
	char	*str;
	char	*st;

	if (s == 0)
	{
		str = "OLDPWD=";
		st = "OLDPWD";
	}
	if (s == 1)
	{
		str = "PWD=";
		st = "PWD";
	}
	main = *data;
	while ((*data))
	{
		if (ft_memcmp(str, (*data)->var_name) == 0
			|| ft_memcmp(st, (*data)->var_name) == 0)
			chenge_old_or_new_comp(data, str, cwd, 0);
		(*data) = (*data)->next;
	}
	*data = main;
}

void	cd_go_home(t_main **main, t_main *data, char *ss)
{
	while (data)
	{
		if (ft_memcmp(data->var_name, "OLDPWD=") == 0
			|| ft_memcmp(data->var_name, "OLDPWD") == 0)
		{
			if (chdir (data->var_value) == 0)
			{
				if (data->var_value[0] == '\0')
				{
					write (2, "minishell: cd: OLDPWD not set\n", 30);
					g_exit_state = 1;
				}
				else
				{
					printf("%s\n", data->var_value);
					change_old_or_new_pwd(main, data->var_value, 1);
					change_old_or_new_pwd(main, ss, 0);
				}
				data = *main;
				break ;
			}
		}
		data = data->next;
	}
}

void	use_chdir_and_change_pwd(char *ss, char **st, t_main **main, char *stt)
{
	int	s;

	s = 0;
	if (st[1][0] == '~' && st[1][1] == '/')
		if_thereis_no_env(main, st[1], 0, ss);
	else if (chdir (st[1]) == 0)
	{
		change_old_or_new_pwd(main, ss, 0);
		stt = getcwd(NULL, 0);
		change_old_or_new_pwd(main, stt, 1);
		free(stt);
	}
	else
	{
		write (2, "minishell: cd: ", 15);
		ft_putstr_fd(st[1], 2);
		write (2, " No such file or directory\n", 27);
		g_exit_state = 1;
	}
}

void	cd_function(t_main **main, char **st, t_main *data)
{
	char	ss[1024];
	char	stt[1024];

	getcwd(ss, sizeof(ss));
	if (ft_memcmp(st[1], "-") == 0)
		cd_go_home(main, data, ss);
	else if (st[1] == '\0' || ft_memcmp(st[1], "~") == 0)
		cd_function_comp(ss, stt, main, data);
	else
		use_chdir_and_change_pwd(ss, st, main, stt);
}
