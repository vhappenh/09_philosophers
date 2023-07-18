NAME := philo

CFLAGS := -Wall -Werror -Wextra

CC := cc -g

OBJ_P := ./obj/

SRC := 	main.c				\
		input_check.c		\
		philosophize.c		\
		philosophize_utils.c\
		universal_utils.c	\
		tasks.c				\
		monitoring.c		\
		ft_free.c

OBJ := $(SRC:%.c=$(OBJ_P)%.o)

$(OBJ_P)%.o:%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@ #-lpthread

.SILENT:

.PHONY:
	all clean fclean re norm

all : $(NAME)

vpath %.c src

$(NAME): $(OBJ)
	echo "compiling..."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	echo 'The executable "philo" was created'

clean:
	$(RM) $(OBJ)
	$(RM) -rd $(OBJ_P)
	echo "The philosophers .o files were removed"

fclean: clean
	$(RM) $(NAME)
	echo "The executable philo was removed"

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader src/*.c src/philosophers.h
