/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:53:00 by afanti            #+#    #+#             */
/*   Updated: 2023/06/10 16:55:42 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_outfile_with_trunc(t_data *data, int s, char **st)
{
	data->fd_stdout = open(st[s + 1], O_CREAT
			| O_RDWR | O_TRUNC, 0777);
	if (data->fd_stdout < 0)
		error_fd(st[s + 1]);
}

char	**return_and_compl(char **str, char **st, int s, int f)
{
	char	**string;
	int		i;

	i = 0;
	string = (char **)ft_calloc(sizeof(char *) * f - 2, 1);
	while (str[i])
	{
		string[i] = str[i];
		i++;
	}
	while (st[s])
	{
		string[i] = ft_strdup(st[s]);
		i++;
		s++;
	}
	free_it(st);
	return (string);
}

char	**out_file_return(char **st, int s, t_data *data)
{
	char	**str;
	int		i;
	int		f;

	f = 0;
	i = 0;
	while (st[f])
		f++;
	str = (char **)ft_calloc(sizeof(char *) * s, 2);
	if (ft_memcm(st[s], ">>") == 0)
		open_outfile_with_append(data, s, st);
	else if (ft_memcm(st[s], ">") == 0)
		open_outfile_with_trunc(data, s, st);
	while (st[i] && i != s)
	{
		str[i] = ft_strdup(st[i]);
		i++;
	}
	i = 0;
	s = s + 2;
	if (st[s] == '\0')
		return (free_it(st), str);
	else
		return (return_and_compl(str, st, s, f));
	return (0);
}

void	sigint_handler(int signum)
{
	(void)signum;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_state = 1;
}

void	lst_free(t_cmd	**cmd)
{
	int	i;

	while ((*cmd))
	{
		i = 0;
		while ((*cmd)->args[i])
		{
			free((*cmd)->args[i]);
			i++;
		}
		free((*cmd)->args);
		(*cmd) = (*cmd)->next;
	}
}
