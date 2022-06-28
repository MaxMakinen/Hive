# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 12:39:13 by leotran           #+#    #+#              #
#    Updated: 2022/06/23 18:16:36 by leotran          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = life
SRC = src/*.c
#SRCS = $(addprefix ./src/, $(SRC))
HEADERS = /includes/
FLAGS = -Wall -Wextra -Werror -I. -Iincludes/
OBJ = *.o

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJ) $(SURPL_O)

fclean: clean
	rm -rf $(NAME) *.out *.gch

re: fclean all