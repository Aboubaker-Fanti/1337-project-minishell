/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:59:48 by afanti            #+#    #+#             */
/*   Updated: 2023/06/11 21:19:04 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*join;

	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!join || !s2 || !s1)
		return (NULL);
	i = -1;
	while (s1 && s1[++i] != '\0')
		join[i] = s1[i];
	j = 0;
	join[i++] = ' ';
	while (s2 && s2[j] != '\0')
		join[i++] = s2[j++];
	join[i] = '\0';
	free(s1);
	return (join);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	c;
	int	s;

	i = 0;
	c = 0;
	s = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		c = c * 10 + (str[i] - 48);
		i++;
	}
	return (c * s);
}

char	*open_file_for_herdoc(t_data *data, int *nbr)
{
	int		i;
	char	*str;
	char	*nb;
	char	*tt;

	str = ft_strdup("/tmp/herdocc123/here_doc_add_");
	i = ft_strlen(str) - 3;
	nb = ft_itoa(nbr[0]);
	str[i + 1] = nb[0];
	str[i + 2] = nb[1];
	free(nb);
	data->fd_herdoc_plan = open(str, O_CREAT | O_RDWR, 0777);
	if (data->fd_herdoc_plan < 0)
	{
		nb = ft_itoa(nbr[0] + data->fd_herdoc_plan);
		str[i + 1] = nb[0];
		str[i + 2] = nb[1];
		free(nb);
		data->fd_herdoc_plan = open(str, O_CREAT | O_RDWR, 0777);
	}
	tt = ft_strdup(str);
	free(str);
	return (tt);
}

static int	ft_len(long i)
{
	int	k;

	k = 0;
	if (i <= 0)
	{
		k++;
		i *= -1;
	}
	while (i)
	{
		i /= 10;
		k++;
	}
	return (k);
}

char	*ft_itoa(int n)
{
	long	s;
	int		c;
	char	*str;

	s = n;
	c = ft_len(s);
	str = malloc(sizeof(char) * (c + 1));
	if (!str)
		return (NULL);
	str[c] = '\0';
	if (s == 0)
		str[0] = '0';
	if (s < 0)
	{
		str[0] = '-';
		s = s * -1;
	}
	while (s > 0)
	{
		str[--c] = 48 + (s % 10);
		s /= 10;
	}
	return (str);
}
