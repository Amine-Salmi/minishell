NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

LIBFT = lib/Libft/libft.a

SRC = 	parse_src/add_spaces.c parse_src/file_utils.c parse_src/free_utils.c parse_src/get_env_utils.c parse_src/get_env_special_case.c \
		parse_src/get_env.c parse_src/minishell_utils.c parse_src/minishell_utils2.c parse_src/minishell_utils3.c \
		parse_src/minishell.c parse_src/parse_split.c parse_src/parse_split_utils.c parse_src/parse_strtrim.c \
		parse_src/syntax_error_utils.c parse_src/syntax_error.c parse_src/token.c parse_src/tokenization_utils.c parse_src/tokenization.c \
		execution_src/built-in/builtin_function.c execution_src/built-in/builtin_utils.c execution_src/built-in/builtin_utils2.c \
		execution_src/built-in/builtin_utils3.c execution_src/built-in/builtin_utils4.c execution_src/built-in/ft_export.c \
		execution_src/built-in/ft_unset.c execution_src/check_path_utils.c execution_src/check_path.c execution_src/env_setup.c \
		execution_src/errors_messg.c execution_src/execute_external.c execution_src/execute_external_utils.c execution_src/execution_utils.c \
		execution_src/execution.c execution_src/handle_signal.c execution_src/heredoc_handler.c execution_src/heredoc_utils.c execution_src/redirection_handler.c

OBJS = $(SRC:.c=.o)

all : $(LIBFT) $(NAME)

$(LIBFT) :
	make -C lib/Libft

$(NAME) : $(LIBFT) $(OBJS) includes/minishell.h
	$(CC) $(CFLAGS) -L ~/.brew/opt/readline/lib/ $(OBJS) $(LIBFT) -o $@ -lreadline

%.o : %.c includes/minishell.h 
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)
	make -C lib/Libft clean

fclean : clean
	$(RM) $(NAME)
	make -C lib/Libft fclean

re : fclean all

.PHONY : clean