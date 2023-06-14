/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting_utiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:41:50 by afanti            #+#    #+#             */
/*   Updated: 2023/06/08 14:30:38 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builting_here(char *st)
{
	if (ft_memcmp(st, "cd") == 0 || ft_memcmp(st, "pwd") == 0
		|| ft_memcmp(st, "export") == 0 || ft_memcmp(st, "unset") == 0
		|| ft_memcmp(st, "env") == 0 || ft_memcmp(st, "echo") == 0
		|| ft_memcmp(st, "exit") == 0)
		return (0);
	return (1);
}

int	check_if_herdoc_or_infile(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (ft_memcm(str[i], "<") == 0)
			return (2);
		i++;
	}
	return (1);
}

void	check_av(char *str)
{
	int	d;
	int	i;

	i = 0;
	d = 0;
	if (str[i] == '\0')
		error_cmd("");
	else if (str[i] == ' ')
	{
		while (str[i])
		{
			if (str[i] == ' ')
				i++;
			else
				break ;
		}
		while (str[d])
			d++;
		if (i == d)
			error_cmd("");
	}
}

int	t_memcmp(const void *s1, const void *s2)
{
	size_t			i;
	unsigned char	*d1;
	unsigned char	*d2;

	i = 0;
	d1 = (unsigned char *) s1;
	d2 = (unsigned char *) s2;
	while (d2[i + 1] && d1[i])
	{
		if (d1[i] != d2[i])
			return (d1[i] - d2[i]);
		i++;
	}
	if (d2[i] == '\n' && d1[i] == '\0')
		return (0);
	else
		return (1);
}

int	ft_memcmp(char *d1, char *d2)
{
	size_t	i;
	size_t	s;
	size_t	k;

	i = 0;
	s = ft_strlen(d1);
	k = ft_strlen(d2);
	if (s != k)
		return (1);
	while (i < s)
	{
		if (d1[i] != d2[i])
		{
			return (d1[i] - d2[i]);
		}
		i++;
	}
	return (0);
}
