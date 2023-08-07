NAME		=	philo
CC			=	@cc
CFLAGS		=	-Wall -Wextra -Werror -pthread
SRC_MANDA	=	events.c philosophers.c parsin.c main.c
OBJ_MANDA	=	$(SRC_MANDA:.c=.o)

all		:	$(NAME)

$(NAME)	: $(OBJ_MANDA)
	@printf "\e[38;5;236m \n ⚡︎⚡︎⚡︎⚡︎⚡︎⚡︎ COMPILING MANDATORY ⚡︎⚡︎⚡︎⚡︎⚡︎⚡︎\n\e[0m\n"
	$(CC) $(CFLAGS) -pthread $(OBJ_MANDA) -o $(NAME)
	@printf "\e[38;5;216m→	successfully mandatory build	✔︎\e[0m\n"

clean	:
	@rm -f $(OBJ_MANDA)
	@printf "\e[38;5;206m→	Objects files deleted 🗑\e[0m\n"

fclean	: clean
	@rm -f $(NAME)
	@printf "\e[38;5;206m→	All files was deleted 🗑\e[0m\n"

re		: fclean all
