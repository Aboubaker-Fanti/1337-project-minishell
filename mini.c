/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:10:05 by afanti            #+#    #+#             */
/*   Updated: 2023/06/13 20:22:33 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_fd_builting(char *s)
{
	int		i;
	char	*str;

	i = 0;
	if (s[0] == '\0')
		return ;
	g_exit_state = 1;
	write (2, "minishell: ", 12);
	while (s[i])
		write (2, &s[i++], 1);
	write (2, ": ", 2);
	i = 0;
	str = strerror(errno);
	while (str[i])
		write (2, &str[i++], 1);
	write (2, "\n", 1);
}

int	check_all_files_if_acesses(char **str, int s, int i)
{
	s = -1;
	while (str[++s])
	{
		if (ft_memcm(str[s], "<") == 0)
			break ;
	}
	while (s != -1)
	{
		if (access(str[s + 1], F_OK) != 0)
		{
			if (i == 5)
				error_fd_builting(str[s + 1]);
			if (i == 2)
				error_fd(str[s + 1]);
			return (1);
		}
		while (str[++s])
		{
			if (ft_memcm(str[s], "<") == 0)
				break ;
		}
		if (str[s] == '\0')
			s = -1;
	}
	return (0);
}

void	print_numeric_argement(char *data)
{
	write (2, "exit\n", 5);
	write (2, "minishell: exit: ", 17);
	ft_putstr_fd(data, 2);
	write (2, " numeric argument required\n", 27);
	exit(255);
}

void	unset_free_first(t_main **main, t_main	*del)
{
	del = (*main);
	(*main) = (*main)->next;
	free_str(del->var_name, del->var_value);
	free(del);
}

void	declare_variables(t_data *data, char **env, t_cmd *lst_cmd)
{
	t_cmd	*dd;

	dd = lst_cmd;
	data->i = 0;
	data->d = 0;
	data->s = 0;
	data->env = env;
	data->to_fork = 0;
	data->herdoc_error = 0;
	data->stdin = dup(0);
	data->stdout = dup(1);
	while (dd)
	{
		data->i++;
		dd = dd->next;
	}
}
