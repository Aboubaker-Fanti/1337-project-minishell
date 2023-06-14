/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:30:13 by brahim            #+#    #+#             */
/*   Updated: 2023/06/10 18:05:15 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst(t_oken **lst)
{
	t_oken	*tmp;

	while (*lst)
	{
		free((*lst)->token);
		free((*lst)->amb);
		tmp = (*lst);
		(*lst) = (*lst)->next;
		free(tmp);
	}
}

void	free_cmd(t_cmd **lst)
{
	int		i;
	t_cmd	*tmp;

	while (*lst)
	{
		free((*lst)->cmd_line);
		if ((*lst)->args)
		{
			i = -1;
			while ((*lst)->args[++i])
				free((*lst)->args[i]);
			free((*lst)->args);
			free((*lst)->exp);
		}
		tmp = (*lst);
		(*lst) = (*lst)->next;
		free(tmp);
	}
}

void	free_str(char *str, char *str2)
{
	free(str);
	free(str2);
}

void	free_it(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_lis(t_cmd **lst)
{
	int		i;
	t_cmd	*stt;

	while ((*lst))
	{
		i = 0;
		stt = *lst;
		(*lst) = (*lst)->next;
		while (stt->args[i])
		{
			free(stt->args[i]);
			i++;
		}
		free(stt->args);
		free(stt->cmd_line);
		free(stt);
	}
}
