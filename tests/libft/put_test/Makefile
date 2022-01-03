# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 12:13:38 by mmakinen          #+#    #+#              #
#    Updated: 2021/11/05 11:54:11 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C =			gcc
FLAGS = 	-Wall -Wextra -Werror -o
NAME =		put_test
SRC_PATH =	../
INCLUDE =	../
SRCS =		$(SRC_PATH)*.c ./*.c
HEADER =	-I $(INCLUDE)  -I ./

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(NAME) $(SRCS) $(HEADER)


clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
