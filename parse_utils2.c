/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <brahim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:36:10 by brahim            #+#    #+#             */
/*   Updated: 2023/06/13 20:38:40 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_cmd(t_cmd *cmd)
{
	int		i;
	char	*cmdl;
	char	*str;

	while (cmd)
	{
		i = -1;
		cmdl = ft_calloc(sizeof(char *) * 1, 1);
		while (cmd->args[++i])
		{
			str = ft_strtrim(cmd->args[i], "\"'");
			cmdl = ft_join(cmdl, str);
			free(str);
		}
		str = ft_strtrim(cmdl, " ");
		cmd->cmd_line = ft_strdup(str);
		free(str);
		free (cmdl);
		cmd = cmd->next;
	}
}

char	*new_line(t_oken **lst)
{
	t_oken	*ls;
	char	*string;
	int		i;
	int		s;

	string = NULL;
	i = 0;
	s = 0;
	ls = *lst;
	while ((*lst))
	{
		string = t_strjoin(string, (*lst)->token);
		string = t_strjoin(string, " ");
		(*lst) = (*lst)->next;
	}
	*lst = ls;
	free_lst(lst);
	return (string);
}

char	*t_strchr(const char *s, int c)
{
	char	*ret;

	ret = (char *)s;
	while (*ret != (char)c)
	{
		if (*ret == '\0')
			return (0);
		ret++;
	}
	return (ret);
}

void	put_amb(t_oken *lst, char *var_n, char *var_v)
{
	if (lst && !var_v[0])
	{
		free(lst->amb);
		lst->amb = ft_strdup(var_n);
	}
}

int	check_pipes(char *str)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (str[i])
	{
		if (str[i] == '|')
			p++;
		i++;
	}
	if (i > 1050)
	{
		write(2, "minishell: fork: Resource temporarily unavailable\n", 50);
		g_exit_state = 1;
		return (0);
	}
	return (1);
}
