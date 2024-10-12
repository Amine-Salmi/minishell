CC = cc

NAME = minishell

SRC = add_spaces.c get_env.c minishell_utils.c minishell.c \
		minishell_utils2.c parse_split.c parse_strtrim.c print_things.c \
		syntax_error.c tokenization.c

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