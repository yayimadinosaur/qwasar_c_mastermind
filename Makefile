CFLAGS = -Wall -Wextra -Werror

NAME = my_mastermind

SRC = ./my_mastermind.c

OBS = ${SRCS:.c=.o}

INCL = ./my_mastermind.h

all: $(NAME)

$(NAME): $(OBJS)

$(OBJS): $(SRC)
	gcc $(CFLAGS) -I $(INCL) -c $(SRC)

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(OBJS) $(NAME)

re: fclean all