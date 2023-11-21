NAME        = minishell
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g3
RM          = rm -rf

OBJ         = $(SRC:.c=.o)

SRC =   ./other/main.c ./lexer/lexer.c ./execution/execute.c ./parser/parser.c ./other/free.c \
		./execution/pipe.c ./other/utils.c ./other/env_change.c ./other/env_change2.c\
		./builtins/env.c ./builtins/echo.c ./builtins/unset.c ./builtins/pwd.c \
		./builtins/export.c ./builtins/exit.c ./builtins/cd.c ./builtins/utilsn.c\
		./lexer/double_lesser.c ./other/utils2.c ./execution/pipe2.c ./lexer/token.c ./parser/parser2.c \
		./other/signals.c ./other/utils3.c ./other/env_change3.c

HEADER = minishell.h 


all:    $(NAME)

%.o : %.c $(HEADER)
			${CC} -c -o $@ $< -I./libft -I/Users/lalvarez/.brew/opt/readline/include ${CFLAGS}

$(NAME):	$(OBJ) 
			${MAKE} -C libft
			$(CC) ${CFLAGS} -o ${NAME} ${OBJ} -L./libft -lft -L/Users/lalvarez/.brew/opt/readline/lib -lreadline -lhistory

libft:
			${MAKE} -C libft

clean:
			$(RM) $(OBJ)
			$(MAKE) -C libft clean

fclean:     clean
			$(RM) $(NAME)
			$(MAKE) -C libft fclean

re:         fclean all

.PHONY:     all libft clean fclean re
