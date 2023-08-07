NAME_BONUS	=	philo_bonus
CC			=	@cc
CFLAGS		=	-Wall -Wextra -Werror -pthread
SRC_BONUS	=	events_bonus.c philosophers_bonus.c parsin_bonus.c main_bonus.c
OBJ_BONUS	=	$(SRC_BONUS:.c=.o)

all		:	$(NAME_BONUS)

$(NAME_BONUS)	: $(OBJ_BONUS)
	@printf "\e[38;5;236m \n ⚡︎⚡︎⚡︎⚡︎⚡︎⚡︎ COMPILING BONUS ⚡︎⚡︎⚡︎⚡︎⚡︎⚡︎\n\e[0m\n"
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS)
	@printf "\e[38;5;216m→	successfully bonus build	✔︎\e[0m\n"

clean	:
	@rm -f $(OBJ_BONUS)
	@printf "\e[38;5;206m→	Objects files deleted 🗑\e[0m\n"

fclean	: clean
	@rm -f $(NAME_BONUS)
	@printf "\e[38;5;206m→	All files was deleted 🗑\e[0m\n"

re		: fclean all

