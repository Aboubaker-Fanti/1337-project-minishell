/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:18:07 by afanti            #+#    #+#             */
/*   Updated: 2023/06/10 14:21:04 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

void	print_export_error(char *str, char *cmd, t_export *data)
{
	int	i;

	i = 0;
	write (2, "minishell: ", 12);
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	i = 0;
	write(2, "\'", 1);
	while (cmd[i])
	{
		write(2, &cmd[i], 1);
		i++;
	}
	write(2, "\'", 1);
	write (2, ": not a valid identifier\n", 25);
	g_exit_state = 1;
	data->good_error = 1;
}

void	complete_change_name_one(t_main **main, char *st, int s, int i)
{
	int	d;

	d = 0;
	while (*main)
	{
		if (d == s)
		{
			free((*main)->var_name);
			free((*main)->var_value);
			(*main)->var_value = malloc(sizeof(char) * i + 1);
			ft_bzero((*main)->var_value, i + 1);
			(*main)->var_name = get_line(st, ft_strlen(st));
		}
		d++;
		(*main) = (*main)->next;
	}
}

void	complete_change_name_on(t_main **main, char *st, int k)
{
	if ((*main)->var_name[ft_strlen((*main)->var_name) - 1] != '=')
	{
		free((*main)->var_name);
		(*main)->var_name = get_line(st, k);
	}
	if ((*main)->var_value)
		free((*main)->var_value);
	(*main)->var_value = ft_strch(st, '=');
}

void	change_name(t_main **main, int i, char *st, int s)
{
	int		d;
	int		k;
	t_main	*data;

	k = 0;
	d = 0;
	data = *main;
	while (st[k] != '=')
		k++;
	if (st[++k] != '\0')
	{
		while (*main)
		{
			if (d == s)
				complete_change_name_on(main, st, k);
			d++;
			(*main) = (*main)->next;
		}
	}
	else
		complete_change_name_one(main, st, s, i);
	*main = data;
}
