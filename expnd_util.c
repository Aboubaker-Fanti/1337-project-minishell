/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnd_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <brahim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:37:05 by afanti            #+#    #+#             */
/*   Updated: 2023/06/13 20:36:56 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char	*str, t_main *shell)
{
	char	*value;

	while (shell)
	{
		if (ft_memcmp(str, shell->var_name) == 0)
		{
			value = ft_strdup(shell->var_value);
			return (value);
		}
		else if (!ft_strncmp(str, "?=", ft_strlen(shell->var_name)))
		{
			value = ft_itoa(g_exit_state);
			g_exit_state = 0;
			return (value);
		}
		shell = shell->next;
	}
	return (ft_calloc(1, 1));
}

void	expand_variables(t_oken *lst, t_main *shell)
{
	while (lst)
	{
		if (lst && !ft_strncmp(lst->token, "<<", 2))
		{
			if (lst->next)
				lst = lst->next;
			else
				return ;
		}
		else if (lst && ft_strchr(lst->token, '$'))
		{
			if (single_quote_check(lst->token))
			{
				lst->token = expand(lst, lst->token, shell);
				lst->exp = 1;
			}
		}
		else if (lst && !ft_strncmp(lst->token, "~", 2))
			lst->token = expand(lst, lst->token, shell);
		lst = lst->next;
	}
}

int	if_there_infile(char **str)
{
	int	s;

	s = 0;
	while (str[s])
	{
		if (ft_memcm(str[s], "<") == 0)
			return (0);
		s++;
	}
	return (1);
}

int	is_cmd(char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strtrim(s, " \t\n");
	if (str[i])
		return (free(str), 1);
	return (free(str), 0);
}

char	*get_var(char *str, int *i, t_main *shell, char **var_n)
{
	int		j;
	char	*var_v;

	j = *i + 1;
	*i += 1;
	if (!ft_strncmp(&str[*i], "?", 1))
		j++;
	else
		while ((ft_isalnum(str[j]) || str[j] == '_'))
			j++;
	(*var_n) = ft_subst(str, *i, j - *i);
	var_v = ft_getenv((*var_n), shell);
	return (var_v);
}
