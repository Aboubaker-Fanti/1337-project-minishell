/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:27:55 by afanti            #+#    #+#             */
/*   Updated: 2023/06/10 18:30:41 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**return_to_pointer(int i, int t, char **str, char **st)
{
	int		s;
	char	**string;

	s = 0;
	string = (char **)ft_calloc(sizeof(char *) * i - 2, 1);
	while (st[s])
	{
		string[s] = ft_strdup(st[s]);
		s++;
	}
	while (str[t])
	{
		string[s] = ft_strdup(str[t]);
		t++;
		s++;
	}
	free_it(str);
	free_it(st);
	return (string);
}

char	**add_to_pointer(char **str, int t)
{
	int		i;
	int		s;
	char	**st;

	i = 0;
	s = 0;
	while (str[i])
		i++;
	st = (char **)ft_calloc(sizeof(char *) * i, 1);
	while (str[s] && s != t)
	{
		st[s] = ft_strdup(str[s]);
		s++;
	}
	s = 0;
	t = t + 2;
	if (str[t] == '\0')
	{
		free_it(str);
		return (st);
	}
	else
		return (return_to_pointer(i, t, str, st));
}

void	main_next_1_comp(t_data *data, char **str, int i, int a)
{
	if (i == 0)
	{
		if (data->nbr_of_pipe > 1 && a != data->nbr_of_pipe - 1
			&& data->o != 0 && data->fd_stdout == 0)
			dup2(data->pipes[1], STDOUT_FILENO);
	}
	if (data->nbr_of_pipe > 1)
		close(data->pipes[0]);
	if (str[0])
	{
		if (access(str[0], X_OK) == 0)
			execve(str[0], str, data->env);
		check_av(str[0]);
		main_next2(data, str, data->env, 0);
	}
	exit(0);
}

int	size_of_2str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	main_next1(t_data *data, char **str, int i, int a)
{
	int		d;
	int		k;

	d = 0;
	data->o = -1;
	while (str[++data->o])
		if (ft_memcm(str[data->o], "<") == 0)
			break ;
	if (i == 2)
		str = check_and_remove_infile(str, data, a, 0);
	data->o = size_of_2str(str);
	if (data->o >= 2 && check_outfile(str) != -1)
	{
		k = check_outfile(str);
		while (k != -1)
		{
			data->o = size_of_2str(str);
			str = out_file(data->o, data, str);
			k = check_outfile(str);
		}
	}
	main_next_1_comp(data, str, i, a);
}
