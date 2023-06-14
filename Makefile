NAME = minishell

CC = CC

READ = -lreadline -L/Users/afanti/Desktop/homebrew/Cellar/readline/8.2.1/lib -I/Users/afanti/Desktop/homebrew/Cellar/readline/8.2.1/include


CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

SRC = minishell.c ft_split.c ft_strtrim.c exec_uti.c mini.c\
		get_next_line/get_next_line.c builting_utiles.c\
		get_next_line/get_next_line_utils.c export_util.c\
		unset.c cd.c fill_env.c ft_listnew.c free.c minishell_utilles.c\
		export.c exec.c minishell_util.c pwd_util.c minishelll.c\
		builting_exec.c expand.c echo_function.c export_utii.c minishel.c\
		file.c parse_utils.c parser.c tokenize.c utils.c utils1.c utils2.c\
		check_err.c parse_utils2.c expnd_util.c tokenize_utils.c\
		export1.c export2.c outfile.c fill_utils.c file_utils.c\

OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(READ) $(CFLAGS)  $(OBJS) -o $(NAME)

clean : 
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
