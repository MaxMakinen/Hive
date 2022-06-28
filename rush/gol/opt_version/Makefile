# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leo <leo@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 12:39:13 by leotran           #+#    #+#              #
#    Updated: 2022/06/23 13:21:50 by leo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = life
SRC = src/*.c
#SRCS = $(addprefix ./src/, $(SRC))
HEADERS = /includes/
FLAGS = -Wall -Wextra -Werror -O3 -I. -Iincludes/
OBJ = *.o

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJ) $(SURPL_O)

fclean: clean
	rm -rf $(NAME) *.out *.gch

re: fclean all