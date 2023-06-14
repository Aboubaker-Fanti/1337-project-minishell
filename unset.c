/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 09:16:40 by afanti            #+#    #+#             */
/*   Updated: 2023/06/13 22:22:49 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	to_com(char *str, char *st)
{
	char	*s;
	int		i;

	i = 0;
	s = malloc(sizeof(char) * ft_strlen(st));
	if (strchh(st, '=') == 1)
	{
		if (ft_memcmp(str, st) == 0)
			return (free(s), 0);
	}
	else
	{
		while (st[i] != '\0' && st[i] != '=')
		{
			s[i] = st[i];
			i++;
		}
		s[i] = '\0';
		if (ft_memcmp(str, s) == 0)
			return (free(s), 0);
	}
	free(s);
	return (1);
}

void	print_unset_error(char *str, char *cmd)
{
	int	i;

	i = 0;
	write (2, "minishell: ", 12);
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	i = 0;
	write(2, "\'", 1);
	while (cmd[i])
	{
		write(2, &cmd[i], 1);
		i++;
	}
	write(2, "\'", 1);
	write (2, ": not a valid identifier\n", 25);
	g_exit_state = 1;
}

int	check_errors(char *split_line)
{
	if (strchh(split_line, '=') == 0)
	{
		print_unset_error("unset: ", split_line);
		return (1);
	}
	if (before_equal(split_line) == 1)
	{
		print_unset_error("unset: ", split_line);
		return (1);
	}
	return (0);
}

void	unset_comp(t_main **main, int i, t_main	*data, char	**split_line)
{
	t_main	*del;

	del = NULL;
	if (to_com(split_line[i], (*main)->var_name) == 0)
		unset_free_first(main, del);
	else
	{
		while ((*main)->next)
		{
			if (to_com(split_line[i], (*main)->next->var_name) == 0)
			{
				del = (*main)->next;
				(*main)->next = (*main)->next->next;
				free_str(del->var_name, del->var_value);
				free(del);
				(*main) = data;
				break ;
			}
			(*main) = (*main)->next;
		}
		*main = data;
	}
}

void	unset_function(t_main **main, char **line)
{
	char	**split_line;
	t_main	*data;
	int		i;
	int		d;

	d = 0;
	i = 1;
	split_line = line;
	while (split_line[i])
	{
		g_exit_state = 0;
		if (to_com(split_line[i], "_") != 0)
		{
			if (check_errors(split_line[i]) == 0)
			{
				data = *main;
				unset_comp(main, i, data, split_line);
			}
		}	
		i++;
	}
}
