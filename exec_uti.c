/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_uti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:11:19 by afanti            #+#    #+#             */
/*   Updated: 2023/06/10 23:11:02 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_folder(t_data *data)
{
	data->foork = fork();
	if (data->foork == 0)
	{
		free(data->temp[0]);
		free(data->temp[1]);
		free(data->temp[2]);
		data->temp[0] = ft_strdup("/bin/rm");
		data->temp[1] = ft_strdup("-rf");
		data->temp[2] = ft_strdup("/tmp/herdocc123");
		data->temp[3] = NULL;
		execve("/bin/rm", data->temp, NULL);
	}
	wait(NULL);
}

int	check_last_file(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (str[i])
	{
		if (ft_memcm(str[i], "<") == 0)
			break ;
		i--;
	}
	return (i);
}

void	main_next2(t_data *data, char **str, char **env, int i)
{
	while (data->main)
	{
		if (ft_memcmp(data->main->var_name, "PATH=") == 0)
			data->path_x = data->main->var_value;
		data->main = data->main->next;
	}
	if (data->path_x == NULL)
		error_cmd(str[0]);
	data->path2d_x = ft_split(data->path_x + 5, ':');
	while (data->path2d_x[i])
	{
		if (str[0][0] == '/')
			error_cmd(str[0]);
		data->command_x = ft_strjoin(data->path2d_x[i], "/");
		data->command_x = ft_strjoin(data->command_x, str[0]);
		if (access(data->command_x, X_OK) == 0)
			execve(data->command_x, str, env);
		free(data->command_x);
		i++;
	}
	error_cmd(str[0]);
}

int	check_if_cmp(char *str, t_main **data, char *st, int is_thre_plus)
{
	int		i;
	int		s;
	t_main	*main;

	main = *data;
	s = 0;
	i = 0;
	while (main)
	{
		if (ft_memcmp(str, main->var_name) == 0)
		{
			if (is_thre_plus == 0)
				change_name(data, ft_strlen(st), st, s);
			if (is_thre_plus == 1)
				change_value_ou_all(data, st, s);
			if (is_thre_plus == 2)
				change_value_all(data, st, s);
			return (0);
		}
		s++;
		main = main->next;
	}
	return (1);
}

t_cmd	*lstlast_cmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
