/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <brahim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:00:47 by afanti            #+#    #+#             */
/*   Updated: 2023/06/13 22:09:19 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_nwe_line(char	**str, int i, int s)
{
	while (str[i] && str[i][0])
	{
		s = 0;
		while (str[i][s])
		{
			if (str[i][0] == '-' && str[i][1] == 'n')
			{
				while (str[i][++s])
				{
					if (str[i][s] != 'n' && str[i][s] != '\0')
					{
						s = -1;
						break ;
					}
				}
				s--;
			}
			if (s == -2 || str[i][0] != '-' || (str[i][0] == '-'
					&& str[i][1] != 'n'))
				return (i);
			s++;
		}
		i++;
	}
	return (i);
}

void	echo_function(char **str, t_main **data)
{
	int	i;
	int	s;

	s = 0;
	i = check_nwe_line(str, 1, 0);
	s = i;
	while (str[s])
	{
		ft_putstr_fd(str[s], (*data)->fd_output);
		if (str[s + 1] != NULL)
			write ((*data)->fd_output, " ", 1);
		s++;
	}
	if (i == 1)
		write ((*data)->fd_output, "\n", 1);
}

int	check_token_comp(t_oken *lst, t_oken	*tmp)
{
	if ((lst->next && ft_strncmp(lst->token, "|", 1))
		&& (is_operator(lst->next->token[0])
			|| (!lst->next->token || !lst->next->token[0])))
	{
		print_stxerr(lst->next->token);
		free_lst(&tmp);
		return (0);
	}
	else if (!lst->next)
	{
		print_stxerr("newline");
		free_lst(&tmp);
		return (0);
	}
	else if ((lst->token[0] == '|' && ft_strlen(lst->token) > 1)
		|| (lst->token[0] == '|' && (lst->next->token[0] == '|')))
	{
		print_stxerr("|");
		free_lst(&tmp);
		return (0);
	}
	return (1);
}

char	*replace_var(char	*str, char	*val, int j, char *var_n)
{
	char	*rep;
	int		i;
	int		k;
	int		size;

	size = ft_strlen(str) - ft_strlen(var_n) + ft_strlen(val);
	rep = ft_calloc(sizeof(char) * (size + 2), 1);
	if (!rep)
		return (NULL);
	i = -1;
	while (str[++i] && i < j)
		rep[i] = str[i];
	k = 0;
	while (val[k])
		rep[i++] = val[k++];
	j++;
	if (str[j] == '?')
		j++;
	else
		while (ft_isalnum(str[j]) || str[j] == '?')
			j++;
	while (str[j])
		rep[i++] = str[j++];
	free(str);
	return (rep);
}

int	var_in_env(char	*str, t_main *shell)
{
	while (shell)
	{
		if (!ft_strncmp(shell->var_name, str, ft_strlen(shell->var_name)))
		{
			free(str);
			return (1);
		}
		shell = shell->next;
	}
	free(str);
	return (0);
}
