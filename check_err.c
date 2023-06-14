/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <brahim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:41:03 by brahim            #+#    #+#             */
/*   Updated: 2023/06/13 20:40:10 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_invalid_chars(char	*str)
{
	int	i;

	if (ft_strchr(str, '"') || ft_strchr(str, '\''))
		return (1);
	i = -1;
	while (str[++i])
	{
		if (str[i] == ';' || str[i] == '{' || str[i] == '&' || str[i] == '}'
			|| str[i] == '[' || str[i] == ']' || str[i] == '{' || str[i] == '('
			|| str[i] == ')' || str[i] == '{' || str[i] == '*' || str[i] == '!')
			return (0);
	}
	return (1);
}

int	check_quotes(char *str)
{
	char	c;
	int		i;
	int		q;

	i = -1;
	q = 0;
	if (ft_strchr(str, '\\'))
		return (print_stxerr("\\"), 1);
	while (str && str[++i])
	{
		if ((str[i] == '"' || str[i] == '\'') && q == 0)
		{
			q = 1;
			c = str[i];
			i++;
		}
		if (str[i] == c)
			q = 0;
	}
	if (q == 1)
		return (write(2, "error: unclosed quotes\n", 23), 1);
	return (0);
}

int	check_errorss(char	*cmd)
{
	int		i;
	char	*pipe;

	i = -1;
	pipe = ft_strtrim(cmd, " \t\n");
	if (!pipe[0])
		return (free(pipe), 1);
	if (pipe[ft_strlen(pipe) - 1] == '|' && pipe[ft_strlen(pipe)] == '\0')
	{
		print_stxerr("|");
		return (free(pipe), 0);
	}
	free (pipe);
	if (check_quotes(cmd))
		return (0);
	while (cmd[++i])
	{	
		if (cmd[i] == '\\')
		{
			print_stxerr("\\");
			return (0);
		}
	}
	return (1);
}

int	check_heredoc(t_oken	*lst)
{
	int	s;

	s = 0;
	while (lst)
	{
		if (ft_memcm(lst->token, "<<") == 0)
			s++;
		lst = lst->next;
	}
	if (s > 16)
	{
		write (2, "minishell: maximum here-document count exceeded\n", 48);
		exit(2);
	}
	return (s);
}

int	check_tokens(t_oken *lst)
{
	t_oken	*tmp;

	tmp = lst;
	if (lst->token[0] == '|')
	{
		print_stxerr("|");
		free_lst(&tmp);
		return (0);
	}
	while (lst)
	{
		if (!check_invalid_chars(lst->token))
		{
			print_stxerr(lst->token);
			free_lst(&tmp);
			return (0);
		}
		if (is_operator(lst->token[0]))
			if (check_token_comp(lst, tmp) == 0)
				return (0);
		lst = lst->next;
	}
	return (1);
}
