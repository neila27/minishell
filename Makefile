NAME        = minishell
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g3
RM          = rm -rf

OBJ         = $(SRC:.c=.o)

SRC =   main.c \
		echo.c \
		pwd.c \

HEADER = minishell.h 


all:    $(NAME)

%.o : %.c $(HEADER)
			${CC} -c -o $@ $< -I./libft -I/opt/homebrew/opt/readline/include ${CFLAGS}
   
$(NAME):    $(OBJ) 
			${MAKE} -C libft
			$(CC) ${CFLAGS} -o ${NAME} ${OBJ} -L./libft -lft -L/opt/homebrew/opt/readline/lib -lreadline -lhistory

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