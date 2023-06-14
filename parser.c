/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:44:03 by brahim            #+#    #+#             */
/*   Updated: 2023/06/12 18:23:06 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_stxerr(char	*str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	g_exit_state = 258;
}

int	define_quote(char c, int *i)
{
	if (c == '\'')
	{
		*i += 1;
		return (1);
	}
	else
	{
		*i += 1;
		return (2);
	}
}

char	*without_quotes(char	*str)
{
	char	*result;
	int		qt;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = ft_calloc((strlen(str) + 1), sizeof(char));
	if (result == NULL)
		return (NULL);
	qt = 0;
	while (str[i] != '\0')
	{
		if (qt == 0 && (str[i] == '\'' || str[i] == '"'))
			qt = define_quote(str[i], &i);
		else if (qt != 0 && ((qt == 1 && str[i] == '\'')
				|| (qt == 2 && str[i] == '"')))
		{
			qt = 0;
			i++;
		}
		else
			result[j++] = str[i++];
	}
	return (free(str), result);
}

void	remove_quotes_char(t_cmd *cmd_lst)
{
	int	i;

	i = 0;
	while (cmd_lst)
	{
		while (cmd_lst->args[i])
		{
			if (ft_strchr(cmd_lst->args[i], '\'')
				|| ft_strchr(cmd_lst->args[i], '"'))
				cmd_lst->args[i] = without_quotes(cmd_lst->args[i]);
			i++;
		}
		cmd_lst = cmd_lst->next;
	}
}

t_cmd	*parse_command(char	*cmd, t_main **exp, t_data *data)
{
	t_oken	*lst;
	t_cmd	*cmd_lst;
	char	*str;

	if (!check_errorss(cmd))
		return (NULL);
	lst = tokenize_str(cmd);
	if (!lst || !check_tokens(lst))
		return (NULL);
	expand_variables(lst, *exp);
	check_ambiguous(lst);
	str = new_line(&lst);
	if (!check_errorss(str))
		return (NULL);
	lst = tokenize_str(str);
	free(str);
	cmd_lst = put_args(lst);
	if (check_heredoc(lst) > 0)
		if (execute_herdoc(&cmd_lst, data, exp) == 80)
			return (NULL);
	free_lst(&lst);
	remove_quotes_char(cmd_lst);
	put_cmd(cmd_lst);
	return (cmd_lst);
}
