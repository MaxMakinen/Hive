# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmalesev <dmalesev@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/08 13:06:32 by dmalesev          #+#    #+#              #
#    Updated: 2022/05/04 12:04:23 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =		gcc
FLAGS =		-Wall -Wextra -Werror
NAME =		fdf
SRCS =		./srcs/*.c
MINXLIB_LIN =	-O -lmlx_Linux -lXext -lX11 -lm
MINXLIB =	-lmlx -framework AppKit -framework OpenGL 
LIBFT =		libft/libft.a

all: $(NAME)

$(NAME):
	make -C libft/ recln
	$(CC) -o $(NAME) $(FLAGS) $(SRCS) $(MINXLIB) $(LIBFT)

linux:
	make -C libft/ recln
	$(CC) -o $(NAME) $(FLAGS) $(SRCS) $(MINXLIB_LIN) $(LIBFT)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
