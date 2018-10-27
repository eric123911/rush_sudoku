NAME		=	sudoku_resolver
CC			=	gcc
CFLAGS +=	-I.
CFLAGS +=	-Wall -Wextra -Werror
FILES		=	main.c \
					sudoku.c
OBJ			=	$(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
				$(CC) -o $(NAME) $(OBJ)

$(OBJ):
				$(CC) $(CFLAGS) -c $(FILES)

clean:
				@echo "\nObject files removed"
				rm -f $(OBJ)

fclean:	clean
				@echo "\n$(NAME) removed"
				rm -f $(NAME)

re: clean fclean all
