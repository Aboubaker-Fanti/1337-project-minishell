/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:21:57 by afanti            #+#    #+#             */
/*   Updated: 2023/06/13 19:18:15 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdu(char *s)
{
	int		i;
	int		len_of_s;
	char	*str;

	i = 0;
	len_of_s = ft_strlen(s);
	str = ft_calloc(sizeof(char *) * len_of_s, 1);
	if (!str)
		return (NULL);
	while (i[s])
	{
		i[str] = i[s];
		i++;
	}
	i[str] = '\0';
	free(s);
	return (str);
}

t_main	*add_node(char *name, char *value)
{
	t_main	*head;

	head = (t_main *)malloc(sizeof(t_main));
	if (!head)
		return (NULL);
	head->var_name = ft_strdu(name);
	head->var_value = ft_strdu(value);
	head->next = NULL;
	return (head);
}

char	*get_line(char *str, int i)
{
	int		s;
	char	*st;

	s = 0;
	st = malloc(sizeof(char) * i + 1);
	while (str[s] && s < i)
	{
		st[s] = str[s];
		s++;
	}
	st[s] = '\0';
	return (st);
}

void	ft_lstadd_back(t_main **lst, t_main *new, int i)
{
	t_main	*current;

	if (i == 0)
	{
		free(*lst);
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
}
