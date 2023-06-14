/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:59:01 by afanti            #+#    #+#             */
/*   Updated: 2023/06/11 21:31:53 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_childe_prosess(t_data *dt, int d, t_main **exp)
{
	if (strchh(dt->dlm, '"') == 0 || strchh(dt->dlm, '\'') == 0)
	{
		dt->dlm = without_quotes(dt->dlm);
		dt->exp_in_hdoc = 1;
	}
	signal(SIGINT, handle_signal1);
	dt->lim = get_next_line(0);
	d = t_memcmp(dt->dlm, dt->lim);
	while (d != 0)
	{
		if (dt->exp_in_hdoc != 1 && strchh(dt->lim, '$') == 0)
			dt->lim = expand(NULL, dt->lim, *exp);
		dt->hdoc = ft_strjoin(dt->hdoc, dt->lim);
		free(dt->lim);
		dt->lim = get_next_line(0);
		d = t_memcmp(dt->dlm, dt->lim);
	}
	write (dt->fd_herdoc_plan, dt->hdoc, ft_strlen(dt->hdoc));
	free(dt->hdoc);
	free(dt->lim);
	free(dt->dlm);
	dt->hdoc = NULL;
	exit(0);
}

int	executr_herdoc_com(t_cmd **cmd, int i, t_main **exp, t_data *dt)
{
	int	d;

	d = 0;
	free_and_change_herdoc_redorection(i, cmd, dt);
	signal(SIGINT, SIG_IGN);
	dt->nbrr++;
	dt->pid = fork();
	if (dt->pid < 0)
		exit(1);
	if (dt->pid == 0)
		in_childe_prosess(dt, d, exp);
	waitpid(dt->pid, &dt->for_exit, 0);
	g_exit_state = WEXITSTATUS(dt->for_exit);
	if (g_exit_state == 88)
	{
		g_exit_state = 1;
		return (80);
	}
	free(dt->dlm);
	return (0);
}

void	delete_or_create_files(t_data *dt)
{
	if (access(dt->temp[1], F_OK) == 0)
	{
		delete_folder(dt);
		free_and_reinit(&dt);
		execve("/bin/mkdir", dt->temp, NULL);
	}
	else
		execve("/bin/mkdir", dt->temp, NULL);
}

int	execute_herdoc(t_cmd **cmd, t_data *dt, t_main **exp)
{
	t_cmd	*dat;
	int		i;

	dat = (*cmd);
	init_t_data(&dt);
	if (dt->foork == 0)
		delete_or_create_files(dt);
	while (wait(NULL) != -1)
		;
	while ((*cmd))
	{
		i = 0;
		while ((*cmd)->args[i])
		{
			if (ft_memcm((*cmd)->args[i], "<<") == 0)
				if (executr_herdoc_com(cmd, i, exp, dt) == 80)
					return (80);
			i++;
		}
		(*cmd) = (*cmd)->next;
	}
	(*cmd) = dat;
	return (0);
}

t_cmd	*put_args(t_oken *lst)
{
	int		i;
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd || !lst)
		return (NULL);
	tmp = cmd;
	while (lst)
	{
		i = 0;
		if (!init_cmd(cmd, lst))
			return (NULL);
		while (lst && ft_strncmp(lst->token, "|", 2))
		{
			if (lst->token[0] != 0)
				copy_data(cmd, lst, &i);
			lst = lst->next;
		}
		cmd->next = NULL;
		if (lst && lst->next)
			add_empty(&cmd, &lst);
	}
	return (tmp);
}
