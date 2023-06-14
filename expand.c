/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <brahim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:32:09 by brahim            #+#    #+#             */
/*   Updated: 2023/06/13 20:42:27 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (1);
	return (0);
}

char	*home_expand(char	*str, t_main *shell)
{
	char	*ret;

	ret = ft_getenv("HOME=", shell);
	free(str);
	return (ret);
}

void	idx_pos(int *i, char *var_v, char *var_n)
{
	if (var_v[0])
		*i += ft_strlen(var_v) - ft_strlen(var_n);
	else
		*i = -1;
}

char	*expand(t_oken *lst, char *str, t_main *shell)
{
	char	*rep;
	char	*var_n;
	char	*var_v;
	int		i;

	i = -1;
	var_n = NULL;
	if (!ft_strncmp(str, "~", 2))
		return (home_expand(str, shell));
	rep = ft_strdup(str);
	while (str[++i])
	{
		if (str[i] == '$' && (str[i + 1] != '\0' && str[i + 1] != ' ')
			&& str[i + 1] != '"')
		{
			var_v = get_var(str, &i, shell, &var_n);
			put_amb(lst, var_n, var_v);
			free (rep);
			rep = replace_var(str, var_v, i - 1, var_n);
			str = ft_strdup(rep);
			idx_pos(&i, var_v, var_n);
			free_str(var_n, var_v);
		}
	}
	return (free(str), rep);
}

int	single_quote_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i += skip_quotes(&str[i]);
			if (!ft_strchr(&str[i], '$'))
				return (0);
		}
		else if (str[i] == '"')
		{
			i += skip_quotes(&str[i]);
			if (!ft_strchr(&str[i], '$'))
				return (1);
		}
		if (str[i] == '$')
			return (1);
		else if (str[i] != '\'' && str[i] != '"')
			i++;
	}
	return (1);
}
