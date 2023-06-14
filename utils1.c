/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:10:33 by afanti            #+#    #+#             */
/*   Updated: 2023/06/11 22:56:52 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handle(int signum)
{
	(void)signum;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_state = 1;
}

void	handle_signal1(int sg)
{
	(void)sg;
	write(2, "\n", 1);
	exit(88);
}

void	init_t_data(t_data **dt)
{
	(*dt)->temp = (char **)ft_calloc(sizeof(char *) * 4, 1);
	(*dt)->temp[0] = ft_strdup("/bin/mkdir");
	(*dt)->temp[1] = ft_strdup("/tmp/herdocc123");
	(*dt)->temp[2] = NULL;
	(*dt)->nbrr = 0;
	(*dt)->exp_in_hdoc = 0;
	(*dt)->foork = fork();
}

void	free_and_reinit(t_data **dt)
{
	free((*dt)->temp[0]);
	free((*dt)->temp[1]);
	free((*dt)->temp[2]);
	(*dt)->temp[0] = ft_strdup("/bin/mkdir");
	(*dt)->temp[1] = ft_strdup("/tmp/herdocc123");
	(*dt)->temp[2] = NULL;
	(*dt)->temp[3] = NULL;
}

void	free_and_change_herdoc_redorection(int i, t_cmd **cmd, t_data *dt)
{
	dt->dlm = ft_strtrim((*cmd)->args[i + 1], " ");
	free((*cmd)->args[i + 1]);
	(*cmd)->args[i + 1] = open_file_for_herdoc(dt, &dt->nbrr);
	free((*cmd)->args[i]);
	(*cmd)->args[i] = ft_strdup("<");
}
