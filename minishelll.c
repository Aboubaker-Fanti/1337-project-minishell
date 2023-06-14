/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishelll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:53:47 by afanti            #+#    #+#             */
/*   Updated: 2023/06/13 23:04:12 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_it(t_data *data, char **env, t_main **main, t_cmd *lst_cmd)
{
	t_data	*dat;
	char	**st;

	declare_variables(data, env, lst_cmd);
	dat = data;
	data->nbr_of_pipe = data->i;
	st = return_command_2d(lst_cmd, 0);
	if (data->nbr_of_pipe == 1)
		exec_builting(lst_cmd, data, st, main);
	while (dat->nbr_of_pipe > data->d && data->s != 5
		&& data->herdoc_error == 0)
	{
		exec_it_complete(data, lst_cmd, main);
		data->d++;
	}
	close(0);
	dup2(data->stdin, 0);
	close(data->stdin);
	if (data->s != 5)
		wait_exit_state(data);
}

void	wait_exit_state(t_data *data)
{
	waitpid(data->pid, &data->for_exit, 0);
	while (wait(NULL) != -1)
		;
	if (data->for_exit == 2)
		g_exit_state = 130;
	else if (data->for_exit == 3)
		(ft_putstr_fd("Quit:\n", 2), g_exit_state = 131);
	else
		g_exit_state = WEXITSTATUS(data->for_exit);
}

int	return_to_aloc(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
}

void	open_outfile_with_append(t_data *data, int s, char **st)
{
	data->fd_stdout = open(st[s + 1], O_CREAT
			| O_RDWR | O_APPEND, 0777);
	if (data->fd_stdout < 0)
		error_fd(st[s + 1]);
}
