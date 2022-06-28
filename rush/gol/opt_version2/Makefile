# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leo <leo@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 12:39:13 by leotran           #+#    #+#              #
#    Updated: 2022/06/23 19:08:21 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = life
SRC = src/*.c
#SRCS = $(addprefix ./src/, $(SRC))
HEADERS = /includes/
FLAGS = -Wall -Wextra -Werror -Ofast -flto -I. -I includes/ -g
OBJ = *.o

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJ) $(SURPL_O)

fclean: clean
	rm -rf $(NAME) *.out *.gch

re: fclean all
