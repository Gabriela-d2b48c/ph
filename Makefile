NAME = philo

SRCS = eat_sleep_think.c \
	init_input_main.c \
	manage_mutexes.c \
	manage_threads.c \
	philo_status.c \
	status_message.c \
	utils.c \

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread -g

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "ʕ•̫͡•ʕ*̫͡*ʕ•͓͡•ʔ-̫͡-ʕ•̫͡•ʔ*̫͡*ʔ-̫͡-ʔ  Philosophers are good to go! ʕ•̫͡•ʕ*̫͡*ʕ•͓͡•ʔ-̫͡-ʕ•̫͡•ʔ*̫͡*ʔ-̫͡-ʔ "

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJS)
	@echo "Cleaning successful"

fclean: clean
	rm -f $(NAME)
	@echo "All generated files are deleted"

re: fclean all
	@echo "Remake completed"

.PHONY: all clean fclean re
