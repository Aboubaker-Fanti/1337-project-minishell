/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:22:29 by afanti            #+#    #+#             */
/*   Updated: 2023/06/13 23:02:53 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/fcntl.h>
# include <string.h>
# include <errno.h>
# include<readline/readline.h>
# include<readline/history.h>
# include "get_next_line/get_next_line.h"
# include <dirent.h>

int	g_exit_state;

typedef struct s_cmd
{
	char			**args;
	int				*exp;
	int				exp_size;
	char			*cmd_line;
	struct s_cmd	*next;
}	t_cmd;

typedef struct t_datta {
	char			**to_parse_it;
	int				nbr_of_pipe;
	int				pipes[2];
	int				pid;
	int				infile;
	int				herdoc;
	int				outfile;
	char			*lim;
	char			*hdoc;
	char			*path_x;
	char			**path2d_x;
	char			*command_x;
	int				fd_stdout;
	int				fd_infile;
	char			**env;
	int				heredocc;
	int				to_fork;
	int				stdin;
	int				stdout;
	t_cmd			*cmd;
	int				herdoc_error;
	int				fd_herdoc_plan;
	int				nbrr;
	int				number;
	int				for_exit;
	int				exp_in_hdoc;
	char			*dlm;
	struct s_main	*main;
	char			**temp;
	int				foork;
	int				s;
	int				i;
	int				d;
	int				o;
}				t_data;

typedef struct s_main
{
	char			*var_name;
	char			*var_value;
	struct s_main	*next;
	int				fd_output;
}			t_main;

typedef struct s_export{
	char	**line;
	int		good_error;
	char	**valid_to_exp;
}			t_export;

typedef struct s_token
{
	char			*token;
	char			*amb;
	int				exp;
	struct s_token	*next;
}	t_oken;

void	free_list(t_oken **lst);
void	rl_replace_line(const char *text, int clear_undo);
char	*ft_strch(char *s, int c);
void	free_it(char **str);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
void	main_next1(t_data *data, char **av, int i, int a);
void	error_cmd(char *s);
void	error_fd(char *s);
int		builting_here(char *st);
void	main_next2(t_data *data, char **str, char **env, int i);
int		check_if_herdoc_or_infile(char **str);
char	*ft_strjoin(char *s1, char *s2);
int		t_memcmp(const void *s1, const void *s2);
int		ft_memcmp(char *d1, char *d2);
char	*ft_strtrim(char *s1, char *set);
int		ft_memcm(char *d1, char *d2);
char	**out_file(int s, t_data *data, char **str);
char	**out_file_return(char **st, int s, t_data *data);
int		check_e(char **st);
void	builting_exec(char *st, char **str, t_main **data);
void	pwd_function(t_main **main);
void	cd_function(t_main **main, char **str, t_main *data);
void	export_function(char **str, t_main **main);
void	unset_function(t_main **main, char **line);
void	prin_env(t_main *main);
void	prin_export(t_main *main);
void	fill_list(t_main **main, char **env);
char	*ft_strchrr(char *s, int c);
char	*ft_strdu(char *s);
t_main	*add_node(char *name, char *value);
char	*get_line(char *str, int i);
void	ft_lstadd_back(t_main **lst, t_main *new, int i);
int		strchh(char *str, int c);
int		before_equal(char *s);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
void	ft_bzero(void *s, size_t n);
void	check_av(char *str);
int		check_outfile(char **st);
void	sigint_handle(int signum);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**return_command_2d(t_cmd *data, int i);
int		execute_herdoc(t_cmd **lst_cmd, t_data *data, t_main **exp);
int		ft_atoi(const char *str);
void	check_and_add_oldpwd(t_main **main);
t_cmd	*parse_command(char	*cmd, t_main **data, t_data *dat);
t_oken	*new_node(char	*data);
char	*get_tok(char	*str);
t_oken	*tokenize_str(char	*str);
t_cmd	*put_args(t_oken *lst);
int		is_operator(char c);
char	*ft_join(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putchar_fd(char c, int fd);
void	expand_variables(t_oken *lst, t_main *shell);
int		ft_isalnum(int c);
char	*new_line(t_oken **lst);
char	*ft_subst(char const *s, unsigned int start, size_t len);
void	echo_function(char **str, t_main **data);
char	*ft_itoa(int n);
char	*without_quotes(char	*str);
char	*expand(t_oken *lst, char *str, t_main *shell);
void	sigint_handler(int signum);
char	*open_file_for_herdoc(t_data *data, int *nbr);
int		check_last_file(char **str);
int		to_com(char *str, char *st);
void	exit_function(char **data);
void	print_stxerr(char	*str);
int		check_ambiguous(t_oken *lst);
void	delete_folder(t_data *data);
void	close_pipes(t_data *data, int d);
int		ft_isdigi(int c);
void	change_old_or_new_pwd(t_main **data, char *cwd, int s);
void	if_thereis_no_env(t_main **main, char *str, int s, char *pwd);
char	**check_and_remove_infile(char **str, t_data *data, int a, int s);
char	**add_to_pointer(char **str, int t);
int		if_there_infile(char **str);
void	exit_function_com(char **data, int i, int s);
char	*home_expand(char	*str, t_main *shell);
char	*new_line(t_oken **lst);
int		check_quotes(char *str);
int		check_errorss(char	*cmd);
void	free_lst(t_oken **lst);
void	free_cmd(t_cmd **lst);
int		check_tokens(t_oken *lst);
int		check_heredoc(t_oken	*lst);
void	put_cmd(t_cmd *cmd);
char	*replace_var(char	*str, char	*val, int j, char *name);
int		check_token_comp(t_oken *lst, t_oken	*tmp);
char	*ft_getenv(char	*str, t_main *shell);
int		single_quote_check(char *str);
void	print_export_error(char *str, char *cmd, t_export *data);
void	export_to_list(t_main **main, char *str);
int		check_if_available(char *str, t_main **data);
void	check_first_char(char **line, t_main **main, t_export *data);
void	change_name(t_main **main, int i, char *st, int s);
void	change_value_ou_all(t_main **main, char *st, int i);
void	change_value_all(t_main **main, char *st, int i);
int		check_if_cmp(char *str, t_main **data, char *st, int is_thre_plus);
void	free_str(char *str, char *str2);
void	add_back(t_oken **lst, t_oken *new);
int		token_size(char	*str);
int		skip_quotes(char	*str);
void	exec_it_complete(t_data *data, t_cmd *lst_cmd, t_main **main);
void	exec_builting(t_cmd *lst_cmd, t_data *data, char **st, t_main **main);
void	declare_variables(t_data *data, char **env, t_cmd *lst_cmd);
int		is_cmd(char *s);
void	free_lis(t_cmd **lst);
void	exec_it(t_data *data, char **env, t_main **main, t_cmd *lst_cmd);
void	open_outfile_with_append(t_data *data, int s, char **st);
int		add_or_creat(char *str, t_main **data);
void	wait_exit_state(t_data *data);
char	*get_var(char *str, int *i, t_main *shell, char **var_n);
void	init_t_data(t_data **dt);
void	free_and_reinit(t_data **dt);
void	handle_signal1(int sg);
void	free_and_change_herdoc_redorection(int i, t_cmd **cmd, t_data *dt);
void	unset_free_first(t_main **main, t_main	*del);
int		check_avail_com(char *str, t_main *main, char *s, char *st);
int		here_execute_else(char *str, t_main **data, char *s, char *st);
void	open_redirect(int y, t_data *data, char **str);
char	**fill_string(int y, char **st, int s, char	**str);
char	*fill_pwd(t_main *data, char *str, int s);
t_cmd	*put_args(t_oken *lst);
void	put_args_com(t_oken *lst, t_cmd *cmd);
void	put_args_comp(t_oken *lst, t_cmd *cmd, int *i);
int		lst_pipe(t_oken *lst);
t_cmd	*lstlast_cmd(t_cmd *lst);
int		init_cmd(t_cmd *cmd, t_oken *lst);
void	copy_data(t_cmd *cmd, t_oken *lst, int *i);
void	add_empty(t_cmd **cmd, t_oken **lst);
t_cmd	*new_node_cmd(char **data);
void	add_back_cmd(t_cmd **lst, t_cmd *new);
void	cd_function_comp(char *ss, char *stt, t_main **main, t_main *data);
int		check_all_files_if_acesses(char **str, int s, int i);
void	print_numeric_argement(char *data);
void	put_amb(t_oken *lst, char *var_n, char *var_v);
int		check_pipes(char *str);

#endif
