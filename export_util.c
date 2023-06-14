/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:16:04 by afanti            #+#    #+#             */
/*   Updated: 2023/06/13 19:18:13 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_first_char_comp(char **line, int i, int con, t_export *data)
{
	if (strchh(line[i], '=') == 0 && con == 0)
	{
		if (before_equal(line[i]) != 0)
			print_export_error("export: ", line[i], data);
	}
	else if ((strchh(line[i], '/') == 0 || before_equal(line[i]) != 0)
		&& con == 0)
		print_export_error("export: ", line[i], data);
}

void	check_first_char(char **line, t_main **main, t_export *data)
{
	int	i;
	int	con;
	int	s;

	s = 0;
	i = 1;
	while (line[i])
	{
		con = 0;
		data->good_error = 0;
		g_exit_state = 0;
		if (check_if_available(line[i], main) == 0)
			con = 1;
		if (line[i][s] == '#' && i == 1)
		{
			prin_export(*main);
			break ;
		}
		if (line[i][s] == '#')
			break ;
		check_first_char_comp(line, i, con, data);
		if (data->good_error == 0 && con == 0)
			export_to_list(main, line[i]);
		i++;
	}
}

int	ft_isdigi(int c)
{
	if ((c >= 48 && c <= 57) || c == '-' || c == '+')
		return (1);
	return (0);
}

char	*ft_strch(char *s, int c)
{
	int		i;
	char	*str;

	i = -1;
	if ((char)c == 0)
		return ((char *)s + ft_strlen(s));
	while (s[++i])
	{
		if (s[i] == (char)c)
			break ;
	}
	str = malloc(sizeof(char) * ((ft_strlen(s) - i) + 1));
	if (s[i] == '\0')
	{
		str[0] = '\0';
		return (str);
	}
	c = 0;
	while (s[++i])
	{
		str[c] = s[i];
		c++;
	}
	str[c] = '\0';
	return (str);
}

void	export_to_list(t_main **main, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' )
		{
			i++;
			break ;
		}
		i++;
	}
	if (!*main)
		ft_lstadd_back(main, add_node(get_line(str, i), ft_strch(str, '=')), 0);
	else
		ft_lstadd_back(main, add_node(get_line(str, i), ft_strch(str, '=')), 1);
}
