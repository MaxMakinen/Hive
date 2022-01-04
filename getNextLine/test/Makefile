# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 10:28:04 by mmakinen          #+#    #+#              #
#    Updated: 2022/01/04 12:07:00 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =		gcc
FLAGS = 	-Wall -Wextra -Werror -g -o
NAME =		GNL_test
SRC_PATH =	./
INCLUDE =	../
SRCS =		test_main.c ../get_next_line.c
OBJECTS =	$(SRCS:.c=.o)
HEADER =	-I $(INCLUDE)
LIBRARY =	../libft/libft.a

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(NAME) $(SRCS) $(LIBRARY) $(HEADER)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re so
