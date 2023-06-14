/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:57:40 by afanti            #+#    #+#             */
/*   Updated: 2023/06/10 22:10:31 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_firstrim(char const *s1, char const *set)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (set[i])
	{
		if (set[i] == s1[c])
		{
			c++;
			i = -1;
		}
		i++;
	}
	return (c);
}

static int	ft_lastrim(char const *s1, char const *set)
{
	int	l;
	int	lens1;

	l = 0;
	if (!s1[0])
		return (0);
	lens1 = ft_strlen(s1);
	while (set[l])
	{
		if (set[l] == s1[lens1 - 1])
		{
			lens1--;
			l = -1;
		}
		l++;
	}
	return (lens1);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		a;
	char	*s2;
	char	*len1;
	int		len2;

	a = 0;
	if (!s1)
		return (NULL);
	if (set == NULL)
		return (ft_strdup((char *)s1));
	len1 = (char *)s1;
	len1 += ft_firstrim(len1, set);
	len2 = ft_lastrim(len1, set);
	if (len2 < 0)
		return (ft_strdup(""));
	s2 = (char *) malloc(sizeof(char) * len2 + 1);
	if (s2 == NULL)
		return (NULL);
	while (len2--)
	{
		s2[a] = len1[a];
		a++;
	}
	s2[a] = '\0';
	return (s2);
}
