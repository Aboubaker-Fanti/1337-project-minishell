/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:23:20 by brahim            #+#    #+#             */
/*   Updated: 2023/06/10 21:43:05 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*sub;

	slen = ft_strlen((char *)s);
	if (len > slen)
		len = slen;
	if (start >= slen)
		return (ft_calloc(1, 1));
	if (len + start > slen)
		sub = (char *)ft_calloc((sizeof(char) * (slen - start)) + 2, 1);
	else
		sub = (char *)ft_calloc(sizeof(char) * (len + 2), 1);
	i = 0;
	if (!sub)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_subst(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*sub;

	slen = ft_strlen((char *)s);
	if (len > slen)
		len = slen;
	if (start >= slen)
		return (ft_calloc(1, 1));
	if (len + start > slen)
		sub = (char *)ft_calloc((sizeof(char *) * (slen - start)) + 2, 1);
	else
		sub = (char *)ft_calloc(sizeof(char) * (len + 2), 1);
	i = 0;
	if (!sub)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '=';
	sub[++i] = '\0';
	return (sub);
}

char	**return_command_2d(t_cmd *data, int i)
{
	int	s;

	s = 0;
	while (data)
	{
		if (s == i)
			return (data->args);
		s++;
		data = data->next;
	}
	return (NULL);
}
