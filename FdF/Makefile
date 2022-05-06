# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 10:28:04 by mmakinen          #+#    #+#              #
#    Updated: 2022/05/06 14:26:50 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =			clang
FLAGS = 		-Wall -Wextra -Werror -O3
NAME =			fdf
SRC_PATH =		./src/
INCLUDE_PATH =	include/ 
VPATH = $(SRC_PATH)
SRCS =			color.c free.c matrix.c projection.c view_control.c draw.c	\
				init.c matrix_manipulation.c rotate.c draw_line.c input.c	\
				mouse.c rot_control.c draw_utils.c keyboard_controls.c		\
				pitch_roll_yaw.c vector.c flatten_zoom.c main.c prep_map.c	\
				vector_manipulation.c
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
