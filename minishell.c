/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:37:39 by afanti            #+#    #+#             */
/*   Updated: 2023/06/13 20:10:34 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_next(char *input, t_data **data, char **env)
{
	t_cmd	*lst;

	if (is_cmd(input) == 1)
	{
		add_history(input);
		lst = parse_command(input, &(*data)->main, (*data));
		if (lst)
			exec_it((*data), env, &(*data)->main, lst);
		free(input);
		free_cmd(&lst);
		free_lis(&lst);
	}
	else
		free(input);
	if (access("/tmp/herdocc123", F_OK) == 0)
	{
		delete_folder((*data));
		if ((*data)->temp)
			free_it((*data)->temp);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_data	*data;

	(void)av;
	(void)ac;
	input = NULL;
	data = ft_calloc(sizeof(t_data), 1);
	data->main = ft_calloc(sizeof(t_main), 1);
	fill_list(&data->main, env);
	check_and_add_oldpwd(&data->main);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		input = readline("minishell$ ");
		if (input == NULL)
			exit(0);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		main_next(input, &data, env);
	}
	return (0);
}

void	open_infile(char **str, t_data *data, int s, int a)
{
	data->fd_infile = open(str[s + 1], O_RDONLY, 0777);
	if (data->fd_infile < 0)
		error_fd(str[s + 1]);
	dup2(data->fd_infile, STDIN_FILENO);
	if (data->nbr_of_pipe > 1 && data->nbr_of_pipe != a + 1)
		dup2(data->pipes[1], STDOUT_FILENO);
}

char	**check_and_remoove_comp(char **str)
{
	int		s;
	char	**st;

	s = 0;
	while (str[s])
		s++;
	st = (char **)ft_calloc(sizeof(char *) * (s + 1), 1);
	s = 0;
	while (str[s])
	{
		st[s] = ft_strdup(str[s]);
		s++;
	}
	free_it(str);
	return (st);
}

char	**check_and_remove_infile(char **str, t_data *data, int a, int s)
{
	check_all_files_if_acesses(str, -1, 2);
	while (str[s])
	{
		if (ft_memcm(str[s], "<") == 0)
			break ;
		s++;
	}
	while (s != -1)
	{
		data->number = check_last_file(str);
		if (s == data->number)
			open_infile(str, data, s, a);
		str = add_to_pointer(str, s);
		s = 0;
		while (str[s])
		{
			if (ft_memcm(str[s], "<") == 0)
				break ;
			s++;
		}
		if (str[s] == '\0')
			s = -1;
	}
	return (check_and_remoove_comp(str));
}
