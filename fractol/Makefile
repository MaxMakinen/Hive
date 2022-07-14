# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 10:28:04 by mmakinen          #+#    #+#              #
#    Updated: 2022/07/14 09:08:07 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =			clang
FLAGS = 		-Wall -Wextra -Werror -O3
NAME =			fractol
SRC_PATH =		./src/
INCLUDE_PATH =	include/ 
VPATH = $(SRC_PATH)
SRCS =			main.c color.c init.c mandelbrot.c julia.c multibrot.c		\
				sierpinsky.c keyboard_controls.c mouse.c render.c	\
				screen.c
LIB =			libft/libft.a
MAC_LIBS =		-lmlx -lm -framework OpenGL -framework AppKit
LINUX_LIBS =	-lX11 -lXext -lmlx -lm
INCLUDES =		-I $(INCLUDE_PATH)
OBJECTS =		$(SRCS:%.c=%.o)



all: $(NAME)

.c.o:
	@$(CC) $(CFLAGS) -c $< $(INCLUDES)

$(NAME): $(OBJECTS) $(LIB)
	@$(CC) $(FLAGS) $(INCLUDES) -o $@ $^ $(MAC_LIBS)

$(LIB):
	@make -C libft/

linux: $(OBJECTS) $(LIB)
	@$(CC) $(FLAGS) $(INCLUDES) -o $(NAME) $^ $(LINUX_LIBS)

debug: fclean $(OBJECTS) debug_libft
	@$(CC) $(FLAGS) -o $(NAME) -g $(OBJECTS) $(LIB) $(INCLUDES)

debug_linux: fclean $(OBJECTS) debug_libft
	@$(CC) $(FLAGS) $(INCLUDES) -o $(NAME) -g $(OBJECTS) $(LIB) $(LINUX_LIBS)

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

re_linux: fclean linux

tidy: all clean

.PHONY: all libclean libfclean clean fclean re tidy linux re_linux
