/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <brahim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:43:29 by brahim            #+#    #+#             */
/*   Updated: 2023/06/13 20:38:55 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_amb(char	*str)
{
	int	i;
	int	n;

	n = ft_strlen(str);
	i = -1;
	ft_putstr_fd("minishell: $", 2);
	while (++i < n - 1)
		ft_putchar_fd(str[i], 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}

int	check_ambiguous(t_oken *lst)
{
	int	i;

	while (lst)
	{
		i = 0;
		if (lst->token[0] != '|' && is_operator(lst->token[0]))
		{
			if (!lst->next->token[0] && lst->next->amb)
				print_amb(lst->next->amb);
		}
		lst = lst->next;
	}
	return (1);
}

int	skip_quotes(char	*str)
{
	int		i;
	char	q;

	i = 1;
	q = str[0];
	while (str[i] && str[i] != q)
		i++;
	return (i + 1);
}

void	skip_spaces(char	**str)
{
	while ((**str) && (**str) == ' ')
		(*str)++;
}

t_oken	*tokenize_str(char	*str)
{
	t_oken	*head;
	int		i;

	head = NULL;
	if (!check_pipes(str))
		return (NULL);
	while (*str)
	{
		i = 0;
		skip_spaces(&str);
		if (*str && is_operator(str[i++]))
		{
			if (is_operator(str[i]) && str[i] == str[i - 1])
				i++;
			add_back(&head, new_node(ft_substr(str, 0, i)));
			str += i;
		}
		else
		{
			i = token_size(str);
			add_back(&head, new_node(ft_substr(str, 0, i)));
			str += i;
		}
	}
	return (head);
}
