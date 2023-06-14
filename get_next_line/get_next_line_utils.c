/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:13:49 by afanti            #+#    #+#             */
/*   Updated: 2023/06/01 16:45:52 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*src;
	size_t			i;

	i = 0;
	src = (unsigned char *)s;
	while (i < n)
	{
		src[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	str = (char *)malloc(count * size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, count * size);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	if (s == NULL)
		return (NULL);
	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*dup;

	i = 0;
	dup = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*t_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	s;
	char	*str;

	s = 0;
	i = 0;
	if (!s1 || s1 == NULL)
		s1 = ft_strdup("");
	str = ft_calloc(ft_strlen(s2) + (ft_strlen(s1) + 1), sizeof(char));
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[s])
	{
		str[i++] = s2[s++];
	}
	free((char *)s1);
	return (str);
}
