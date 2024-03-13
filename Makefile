NAME = get_next_line.out

SRC = get_next_line.c \
		get_next_line_utils.c

OBJS = $(SRC:.c=.o)

.c.o:
	@cc -c $(FLAGS) $(SRC)

all: $(SRC)
	@cc $(FLAGS) $(OBJS) -o $(NAME) -L ./

clean:
	@rm -rf *.o

fclean: clean
	@rm -rf *.out

re: fclean all
