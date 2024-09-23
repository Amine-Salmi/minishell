CC = cc

NAME = minishell

SRC = minishell.c minishell_utils.c minishell_utils2.c\
		ft_split.c syntax_error.c tokenization.c print_things.c\
		get_env.c\

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) -lreadline  $(OBJ) -g -fsanitize=address -o $(NAME)

%.o:%.c minishell.h
	$(CC) -c $< -o $@

clean :
	$(RM) *.o

fclean : clean
	$(RM) $(NAME)

re : fclean all