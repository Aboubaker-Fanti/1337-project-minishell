/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 00:10:08 by afanti            #+#    #+#             */
/*   Updated: 2023/06/11 00:10:33 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_cmd(t_cmd *cmd, t_oken *lst)
{
	cmd->args = ft_calloc(sizeof(char *) * (lst_pipe(lst) + 5), 1);
	cmd->exp = ft_calloc((lst_pipe(lst)), sizeof(int));
	cmd->exp_size = lst_pipe(lst);
	if (!cmd->args || !cmd->exp)
		return (0);
	return (1);
}

void	copy_data(t_cmd *cmd, t_oken *lst, int *i)
{
	free (cmd->args[*i]);
	cmd->args[*i] = ft_strdup(lst->token);
	cmd->exp[*i] = lst->exp;
	*i += 1;
}

void	add_empty(t_cmd **cmd, t_oken **lst)
{
	add_back_cmd(cmd, new_node_cmd(NULL));
	(*cmd) = (*cmd)->next;
	(*lst) = (*lst)->next;
}
