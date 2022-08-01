# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 10:28:04 by mmakinen          #+#    #+#              #
#    Updated: 2022/08/01 11:27:16 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL =			/bin/sh
.SUFFIXES =		
.SUFFIXES =		.c .o .h
CC =			clang
FLAGS = 		-Wall -Wextra -Werror -O3
NAME =			fractol
SRC_DIR =		src
INC_DIR =		include
OBJ_DIR =		obj
SRCS =			main.o color.o init.o mandelbrot.o julia.o multibrot.o		\
				keyboard_controls.o mouse.o render.o screen.o img.o \
				multithread.o
LIB =			libft/libft.a
MAC_LIBS =		-lmlx -lm -framework OpenGL -framework AppKit
LINUX_LIBS =	-lX11 -lXext -lmlx -lm -lpthread
INCLUDES =		-I $(INC_DIR)/
OBJECTS =		$(addprefix $(OBJ_DIR)/, $(SRCS))



all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) -o $@ $< $(INCLUDES)

$(NAME): $(OBJECTS) $(LIB)
	$(CC) $(FLAGS) $(INCLUDES) -o $@ $^ $(MAC_LIBS)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

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
	rm -rf $(OBJ_DIR)

fclean: clean libfclean
	rm -f $(NAME)

re: fclean all

re_linux: fclean linux

tidy: all clean

.PHONY: all libclean libfclean clean fclean re tidy linux re_linux
