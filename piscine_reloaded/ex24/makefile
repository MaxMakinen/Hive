# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 12:13:38 by mmakinen          #+#    #+#              #
#    Updated: 2021/11/03 16:02:10 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C =			gcc
FLAGS = 	-Wall -Wextra -Werror -c
NAME =		libft.a
SRC_PATH =	./srcs/
INCLUDE =	./includes/
SRCS =		$(SRC_PATH)ft_putchar.c $(SRC_PATH)ft_putstr.c $(SRC_PATH)ft_strcmp.c $(SRC_PATH)ft_strlen.c $(SRC_PATH)ft_swap.c
OBJECTS =	ft_putchar.o ft_putstr.o ft_strcmp.o ft_strlen.o ft_swap.o
HEADER =	-c -I $(INCLUDE)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)

$(OBJECTS):
	$(CC) $(FLAGS) $(SRCS) $(HEADER)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
