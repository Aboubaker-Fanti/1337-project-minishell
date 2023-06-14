/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:59:04 by afanti            #+#    #+#             */
/*   Updated: 2023/05/27 13:31:09 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*jib9blmnnewline(char *str)
{
	int		i;
	char	*ret;

	if (!str)
		return (NULL);
	if (!ft_strchr((const char *)str, '\n'))
		return (str);
	i = 0;
	ret = 0;
	ret = ft_calloc((ft_strlen(str) + 1), sizeof(char));
	while (str[i] != '\n')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\n';
	return (ret);
}

char	*afternewline(char *st)
{	
	int		nfound;
	char	*ret;
	int		i;

	i = 0;
	while (st[i])
	{
		if (st[i] == '\n')
			break ;
		i++;
	}
	if (st[i] == '\0')
		i = 0;
	nfound = i;
	ret = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	i = 0;
	while (st[++nfound])
	{
		ret[i] = st[nfound];
		i++;
	}
	free(st);
	return (ret);
}

char	*get_next_line_cal(int fd, int i, char *str)
{
	static char	*st;
	char		*ret;
	char		*temp;

	while (i && !ft_strchr((const char *)st, '\n'))
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i == -1)
		{
			if (st)
				free(st);
			return (free(str), st = NULL, NULL);
		}
		if (i == 0)
		{
			if (ft_strlen(st) > 0)
				return (temp = st, free(str), st = NULL, temp);
			return (free(str), free(st), st = NULL, NULL);
		}
		st = t_strjoin(st, str);
	}
	ret = jib9blmnnewline(st);
	return (free(str), st = afternewline(st), ret);
}

char	*get_next_line(int fd)
{
	char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	return (get_next_line_cal(fd, 1, str));
}
