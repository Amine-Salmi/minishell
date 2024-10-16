NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
RM = rm -rf

LIBFT = lib/Libft/libft.a

SRC =  $(wildcard parse_src/*.c) $(wildcard execution_src/*.c)
OBJS = $(SRC:.c=.o)

all : $(LIBFT) $(NAME)

$(LIBFT) :
	make -C lib/Libft

$(NAME) : $(LIBFT) $(OBJS) includes/minishell.h 
	$(CC) $(OBJS) $(LIBFT) -o $@ -lreadline

%.o : %.c includes/minishell.h 
	$(CC) -c $< -o $@

clean :
	$(RM) $(OBJS)
	make -C lib/Libft clean

fclean : clean
	$(RM) $(NAME)
	make -C lib/Libft fclean

re : fclean all

.PHONY : clean