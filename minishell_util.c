/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:42:57 by afanti            #+#    #+#             */
/*   Updated: 2023/06/12 18:12:56 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	s;
	char	*str;

	s = 0;
	i = 0;
	if (!s1)
		s1 = ft_strdup("");
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[s])
	{
		str[i++] = s2[s++];
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

int	ft_memcm(char *d1, char *d2)
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
			return (d1[i] - d2[i]);
		i++;
	}
	return (0);
}

void	error_cmd(char *s)
{
	int	i;

	i = 0;
	g_exit_state = 1;
	write (2, "minishell: ", 11);
	while (s[i])
		write (2, &s[i++], 1);
	if (s[0] == ' ')
		write (2, ": permission denied:\n", 22);
	else if (s[0] == '.' && s[1] == '\0')
	{
		write (2, ": filename argument required\n", 29);
		g_exit_state = 2;
	}
	else if (s[0] == '/')
		write (2, ": No such file or directory\n", 28);
	else if (s[0] != '/')
	{
		write (2, ": command not found\n", 20);
		g_exit_state = 127;
	}
	exit(g_exit_state);
}

void	error_fd(char *s)
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
	exit (g_exit_state);
}

void	close_pipes(t_data *data, int d)
{
	if (data->fd_stdout > 0)
	{
		close(data->pipes[1]);
		close(data->pipes[0]);
	}
	else
	{
		close(data->pipes[1]);
		if (data->nbr_of_pipe > d)
			dup2(data->pipes[0], STDIN_FILENO);
		close(data->pipes[0]);
	}
}
