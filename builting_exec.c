/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <brahim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:27:15 by afanti            #+#    #+#             */
/*   Updated: 2023/06/13 22:09:29 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builting_exec(char *st, char **str, t_main **data)
{
	if (ft_memcmp(st, "echo") == 0)
		echo_function(str, data);
	if (ft_memcmp(st, "cd") == 0)
		cd_function(data, str, *data);
	else if (ft_memcmp(st, "pwd") == 0)
		pwd_function(data);
	else if (ft_memcmp(st, "export") == 0)
		export_function(str, data);
	else if (ft_memcmp(st, "unset") == 0)
		unset_function(data, str);
	else if (ft_memcmp(st, "env") == 0)
		prin_env(*data);
	else if (ft_memcmp(st, "exit") == 0)
		exit_function(str);
}

void	exit_function(char **data)
{
	int	i;
	int	s;

	g_exit_state = 0;
	if (!data[1])
		exit(0);
	i = 0;
	while (data[++i])
	{
		s = -1;
		while (data[i][++s])
		{
			if (i == 1 && ft_isdigi(data[i][s]) == 0)
				g_exit_state = 255;
		}
	}
	if (i > 2 && g_exit_state != 255)
	{
		write (2, "exit\n", 5);
		write (2, "minishell: exit: too many arguments\n", 36);
		g_exit_state = 1;
	}
	if (g_exit_state == 255)
		g_exit_state = 0;
	exit_function_com(data, 1, 0);
}

void	prin_env(t_main *main)
{
	int		i;
	t_main	*cpy;
	int		c;

	i = 0;
	if (main)
	{
		c = main->fd_output;
		cpy = main;
		while (cpy != NULL)
		{
			if (cpy->var_name[ft_strlen(cpy->var_name) - 1] == '=')
			{
				ft_putstr_fd(cpy->var_name, c);
				ft_putstr_fd(cpy->var_value, c);
				ft_putstr_fd("\n", c);
			}
			cpy = cpy->next;
		}
	}
}

void	prin_export(t_main *main)
{
	int		c;
	int		i;
	int		d;

	d = 0;
	i = 0;
	if (main)
	{
		c = main->fd_output;
		while (main != NULL)
		{
			write (c, "declare -x ", 11);
			ft_putstr_fd(main->var_name, c);
			if (main->var_name[ft_strlen(main->var_name) - 1] == '=')
				ft_putstr_fd("\"", c);
			ft_putstr_fd(main->var_value, c);
			if (main->var_name[ft_strlen(main->var_name) - 1] == '=')
				ft_putstr_fd("\"", c);
			ft_putstr_fd("\n", c);
			main = main->next;
		}
	}
}

char	*ft_strchrr(char *s, int c)
{
	int		i;
	char	*str;

	i = -1;
	if ((char)c == 0)
		return ((char *)s + ft_strlen(s));
	while (s[++i])
	{
		if (s[i] == (char)c)
			break ;
	}
	str = malloc(sizeof(char) * (ft_strlen(s) - i) + 1);
	if (s[i] == '\0')
	{
		str[0] = '\0';
		return (str);
	}
	c = 0;
	while (s[++i])
	{
		str[c] = s[i];
		c++;
	}
	str[c] = '\0';
	return (str);
}
