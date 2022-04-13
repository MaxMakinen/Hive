# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 10:28:04 by mmakinen          #+#    #+#              #
#    Updated: 2022/04/13 10:12:01 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =		clang
#FLAGS = 	-Wall -Wextra -Werror -g -lmlx -framework OpenGL -framework AppKit
FLAGS = 	-Wall -Wextra -Werror -g -lX11 -lXext -lmlx
CFLAGS =	-Wall -Wextra -Werror -g $(HEADER)
NAME =		fdf
SRC_PATH =	./src/
INCLUDE_PATH = ./include/ 
VPATH +=	$(SRC_PATH)
VPATH +=	$(INCLUDE_PATH)
SRCS =		test.c input.c
LIB =		libft/libft.a
OBJECTS =	$(SRCS:%.c=%.o)
HEADER =	-I $(INCLUDE_PATH)

all: $(NAME)

$(NAME): $(OBJECTS) $(LIB)
	@$(CC) $(FLAGS) -o $@ $^ $(HEADER)

$(LIB):
	@make -C libft/

debug: fclean $(OBJECTS) debug_libft
	@$(CC) $(FLAGS) $(NAME) -g $(OBJECTS) $(LIB) $(HEADER)

debug_libft:
	@make -C libft/ debug

libclean:
	@make -C libft/ clean

libfclean:
	rm -f $(LIB)

clean: libclean
	rm -f $(OBJECTS) 

fclean: clean libfclean
	rm -f $(NAME)

re: fclean all

tidy: all clean

.PHONY: all libclean libfclean clean fclean re tidy
