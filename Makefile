SRC = sources/main.c \
sources/path_finder.c \
sources/child1.c \
sources/pip_utils.c \
sources/child2.c

CC = cc

COMP_FLAGS= -Wall -Wextra -Werror

NAME = pipex

OBJS := $(SRC:%.c=%.o)

%.o: %.c 
	$(CC) $(COMP_FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@cd libft && $(MAKE) --no-print-directory && $(MAKE) --no-print-directory bonus
	@$(CC) $(COMP_FLAGS) -o $(NAME) $(OBJS) ./libft/libft.a


.PHONY: clean fclean re all test

all: $(NAME)

clean:
	@cd libft --no-print-directory && $(MAKE) --no-print-directory fclean
	@rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: 
	valgrind --leak-check=full --trace-children=yes --track-fds=yes ./pipex input.txt "cat" "wc -l" output   