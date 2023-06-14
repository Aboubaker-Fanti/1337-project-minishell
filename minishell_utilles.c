/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utilles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:36:38 by afanti            #+#    #+#             */
/*   Updated: 2023/06/13 23:01:25 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builting_compl(char **st, t_main **main)
{
	if (if_there_infile(st) != 0)
		builting_exec(st[0], st, main);
}

void	exec_builting(t_cmd *lst_cmd, t_data *data, char **st, t_main **main)
{
	if (*main)
		(*main)->fd_output = 1;
	if (builting_here(st[0]) == 0)
	{
		if (if_there_infile(st) == 0)
		{
			if (check_all_files_if_acesses(st, -1, 5) == 0)
				st = check_and_remove_infile(st, data, 0, 0);
			lst_cmd->args = st;
		}
		data->s = check_outfile(st);
		if (data->s != -1)
		{
			while (data->s != -1)
			{
				st = out_file_return(st, data->s, data);
				(*main)->fd_output = data->fd_stdout;
				data->s = check_outfile(st);
				if (data->s == -1)
					lst_cmd->args = st;
			}
		}
		exec_builting_compl(st, main);
		data->s = 5;
	}
}

void	heredoc_exec(t_data *data, char **str, t_main **main)
{
	if (if_there_infile(str) == 0)
		str = check_and_remove_infile(str, data, data->d, 0);
	if (*main)
		(*main)->fd_output = 1;
	data->i = check_outfile(str);
	if (data->i != -1)
	{
		while (data->i != -1)
		{
			str = out_file_return(str, data->i, data);
			if (*main)
				(*main)->fd_output = data->fd_stdout;
			data->fd_stdout = 0;
			data->i = check_outfile(str);
		}
	}
	else if (data->nbr_of_pipe != data->d + 1)
		dup2(data->pipes[1], STDOUT_FILENO);
	builting_exec(str[0], str, main);
	exit(0);
}

void	exec_all_here(t_data *data, char **str, t_main **main)
{
	if (data->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (builting_here(str[0]) == 0)
			heredoc_exec(data, str, main);
		else
			main_next1(data, str, data->s, data->d);
	}
	if (data->nbr_of_pipe > 1 || data->s == 1 || data->s == 2)
		close_pipes(data, data->d);
	if (data->fd_stdout > 2)
	{
		dup2(1, data->fd_stdout);
		close(1);
		close(data->fd_stdout);
	}
}

void	exec_it_complete(t_data *data, t_cmd *lst_cmd, t_main **main)
{
	char	**str;

	data->heredocc = 0;
	data->s = 0;
	data->fd_stdout = 0;
	str = return_command_2d(lst_cmd, data->d);
	if (check_if_herdoc_or_infile(str) == 0
		|| check_if_herdoc_or_infile(str) == 2)
	{
		if (check_if_herdoc_or_infile(str) == 2)
			data->s = 2;
	}
	if (data->nbr_of_pipe > 1 || data->s == 1)
	{
		if (pipe(data->pipes) < 0)
			exit(1);
	}
	data->pid = fork();
	if (data->pid < 0)
		exit(1);
	signal(SIGINT, SIG_IGN);
	exec_all_here(data, str, main);
}
