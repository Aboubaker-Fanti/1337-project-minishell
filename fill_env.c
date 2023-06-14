/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:28:16 by afanti            #+#    #+#             */
/*   Updated: 2023/06/11 22:56:30 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_list_if_not_env(t_main **main)
{
	char	*str;
	char	*st;
	char	*string;
	char	ss[1024];

	getcwd(ss, sizeof(ss));
	str = ft_strdup("OLDPWD");
	st = ft_strdup("PWD=");
	string = ft_strdup("SHLVL=1");
	ft_lstadd_back(main, add_node(get_line(str, 6), ft_strch(str, '=')), 0);
	ft_lstadd_back(main, add_node(get_line(st, 3), ft_strch(st, '=')), 1);
	change_old_or_new_pwd(main, ss, 1);
	ft_lstadd_back(main, add_node(get_line(string, 6),
			ft_strch("SHLVL=1", '=')), 1);
	free(str);
	free(st);
	free(string);
}

void	fill_struct_comp(t_main **main, char **env, int i, int j)
{
	char	*str;

	str = ft_strch(env[i], '=');
	ft_lstadd_back(main, add_node(get_line(env[i], j), str), 1);
}

void	fill_struct(t_main **main, char **env, char	*str, t_main *new)
{
	int	j;
	int	i;

	i = -1;
	while (env[++i])
	{
		j = -1;
		while (env[i][++j])
		{
			if (env[i][j] == '=')
			{
				j++;
				if (i == 0)
				{
					str = ft_strch(env[i], '=');
					new = add_node(get_line(env[i], j), str);
					ft_lstadd_back(main, new, 0);
				}
				else
					fill_struct_comp(main, env, i, j);
				break ;
			}
		}
	}
}

void	fill_list(t_main **main, char **env)
{
	int		i;
	int		j;
	char	*str;
	t_main	*new;

	str = NULL;
	new = NULL;
	i = 0;
	j = 0;
	while (env[i])
		i++;
	if (i == 0)
		fill_list_if_not_env(main);
	else
		fill_struct(main, env, str, new);
}

int	before_equal(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '\0')
		return (1);
	if (ft_isalpha(s[i]) == 0 && s[i] != '_')
		return (1);
	i++;
	while (s[i] != '\0' && s[i] != '=')
	{
		if (ft_isdigit(s[i]) == 0 && ft_isalpha(s[i]) == 0 && s[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
