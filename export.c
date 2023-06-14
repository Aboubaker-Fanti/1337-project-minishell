/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:31:45 by afanti            #+#    #+#             */
/*   Updated: 2023/06/12 19:16:04 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_if_there_plus(char *str, t_main **data, char *s, char *st)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	if (strchh(str, '+') == 0 && str[i - 1] == '+')
	{
		if (add_or_creat(str, data) == 0)
			return (free(s), free(st), 0);
		return (1);
	}
	else
		if (here_execute_else(str, data, s, st) == 0)
			return (0);
	return (1);
}

int	check_if_available(char *str, t_main **data)
{
	char	*st;
	char	*s;
	int		i;
	t_main	*main;

	main = *data;
	st = malloc(sizeof(char) * ft_strlen(str) + 1);
	s = malloc(sizeof(char) * ft_strlen(str) + 2);
	i = 0;
	if (strchh(str, '=') == 0)
	{
		if (execute_if_there_plus(str, data, s, st) == 0)
			return (0);
	}
	else
	{
		if (check_avail_com(str, main, s, st) == 0)
			return (0);
	}
	return (free(st), free(s), 1);
}

int	check_avail_com(char *str, t_main *main, char *s, char *st)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '=';
	s[++i] = '\0';
	while (main)
	{
		if (ft_memcmp(str, main->var_name) == 0
			|| ft_memcmp(s, main->var_name) == 0)
			return (free(s), free(st), 0);
		main = main->next;
	}
	return (1);
}

void	export_function(char **str, t_main **main)
{
	t_export	*data;
	int			i;
	int			d;

	d = 0;
	i = 0;
	data = ft_calloc(sizeof(t_export), 1);
	if (!str[1])
		prin_export(*main);
	else
		check_first_char(str, main, data);
	free(data);
}

void	cd_function_comp(char *ss, char *stt, t_main **main, t_main *data)
{
	int	i;

	while (data)
	{
		if (ft_memcmp(data->var_name, "HOME=") == 0)
		{
			if (chdir (data->var_value) == 0)
			{
				change_old_or_new_pwd(main, ss, 0);
				stt = getcwd(NULL, 0);
				change_old_or_new_pwd(main, stt, 1);
				free(stt);
				i = 5;
			}
		}
		data = data->next;
	}
	if (i != 5)
	{
		write (2, "minishell: cd: HOME not set\n", 28);
		g_exit_state = 1;
	}
}
