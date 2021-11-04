# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 12:13:38 by mmakinen          #+#    #+#              #
#    Updated: 2021/11/03 14:32:33 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C =			gcc
FLAGS = 	-Wall -Wextra -Werror -o
NAME =		ft_display_file
SRC_PATH =	./
INCLUDE =	./
SRCS =		$(SRC_PATH)func.c
HEADER =	-I $(INCLUDE)

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(NAME) $(SRCS) $(HEADER)


clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
