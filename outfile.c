/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <brahim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:11:48 by brahim            #+#    #+#             */
/*   Updated: 2023/06/10 19:12:03 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_redirect(int y, t_data *data, char **str)
{
	if (ft_memcm(str[y], ">") == 0)
	{
		data->fd_stdout = open(str[y + 1], O_CREAT
				| O_RDWR | O_TRUNC, 0777);
		if (data->fd_stdout < 0)
			error_fd(str[y + 1]);
	}
	else if (ft_memcm(str[y], ">>") == 0)
	{
		data->fd_stdout = open(str[y + 1], O_CREAT
				| O_RDWR | O_APPEND, 0777);
		if (data->fd_stdout < 0)
			error_fd(str[y + 1]);
	}
}

char	**fill_string(int y, char **st, int s, char	**str)
{
	char	**string;
	int		d;

	d = -1;
	y = y + 2;
	string = (char **)ft_calloc(sizeof(char *) * s - 1, 1);
	while (st[++d])
		string[d] = ft_strdup(st[d]);
	while (str[y])
		string[d++] = ft_strdup(str[y++]);
	string[d] = NULL;
	return (free_it(str), string);
}

char	**out_file(int s, t_data *data, char **str)
{
	char	**st;
	int		d;
	int		y;

	y = -1;
	d = -1;
	while (str[++y])
		if (ft_memcm(str[y], ">") == 0 || ft_memcm(str[y], ">>") == 0)
			break ;
	open_redirect(y, data, str);
	dup2(data->fd_stdout, STDOUT_FILENO);
	while (str[s])
		s++;
	st = (char **)ft_calloc(sizeof(char *) * s - 1, 1);
	while (str[++d] && y > d)
		st[d] = ft_strdup(str[d]);
	st[d] = NULL;
	if (str[y + 2] == '\0')
		return (free_it(str), st);
	else
		return (fill_string(y, st, s, str));
}

int	check_outfile(char **st)
{
	int	s;

	s = 0;
	while (st[s])
	{
		if (ft_memcm(st[s], ">") == 0 || ft_memcm(st[s], ">>") == 0)
			return (s);
		s++;
	}
	return (-1);
}
