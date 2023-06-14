/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:48:15 by brahim            #+#    #+#             */
/*   Updated: 2023/06/09 17:29:49 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

t_oken	*lstlast(t_oken *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_oken	*new_node(char *data)
{
	t_oken	*node;

	node = (t_oken *)malloc(sizeof(t_oken));
	if (!node)
		return (NULL);
	node->token = data;
	node->amb = NULL;
	node->next = NULL;
	return (node);
}

void	add_back(t_oken **lst, t_oken *new)
{
	t_oken	*temp;

	if (lst)
	{
		if (*lst == NULL || !(*lst))
			*lst = new;
		else
		{
			temp = lstlast(*lst);
			temp->next = new;
		}
	}
}

int	token_size(char	*str)
{
	int	i;

	i = 0;
	while (str[i] && (!is_operator(str[i]) && str[i] != ' '))
	{
		if (str[i] && (str[i] == '\'' || str[i] == '"'))
			i += skip_quotes(&str[i]);
		else
			i++;
	}
	return (i);
}
