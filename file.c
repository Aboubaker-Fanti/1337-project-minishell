/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:36:54 by brahim            #+#    #+#             */
/*   Updated: 2023/06/11 00:08:53 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_node_cmd(char **data)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->args = data;
	node->next = NULL;
	return (node);
}

void	add_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*temp;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			temp = lstlast_cmd(*lst);
			temp->next = new;
		}
	}
}

int	lst_pipe(t_oken *lst)
{
	int	i;

	i = 0;
	while (lst && ft_strncmp(lst->token, "|", 2))
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
