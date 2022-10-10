# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 10:28:04 by mmakinen          #+#    #+#              #
#    Updated: 2022/09/01 10:46:23 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL =			/bin/sh
.SUFFIXES =		
.SUFFIXES =		.c .o .h
CC =			clang
FLAGS = 		-Wall -Wextra -Werror -g
NAME =			RTv1
SRC_DIR =		src
INC_DIR =		include
OBJ_DIR =		obj
SRCS =			main.o init.o keyboard_controls.o render.o img.o raytrace.o \
				brightness.o vector_math.o input.o ft_bit.o ft_clamp.o ft_swapf.o\
				cone_intersect.o cylinder_intersect.o sphere_intersect.o quaternion.o\
				get_surface.o plane.o shade_ray.o
LIB =			libft/libft.a
MAC_LIBS =		-lmlx -lm -framework OpenGL -framework AppKit
LINUX_LIBS =	-lX11 -lXext -lmlx -lm -lpthread
INCLUDES =		-I $(INC_DIR)/
OBJECTS =		$(addprefix $(OBJ_DIR)/, $(SRCS))


all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) -g -o $@ $< $(INCLUDES)

$(NAME): $(OBJECTS) $(LIB)
	$(CC) $(FLAGS) $(INCLUDES) -o $@ $^ $(MAC_LIBS)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(LIB):
	@make -C libft/

linux: $(OBJECTS) $(LIB)
	@$(CC) $(FLAGS) $(INCLUDES) -o $(NAME) -g $^ $(LINUX_LIBS)

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

tidy:
	rm -rf $(OBJ_DIR)

.PHONY: all libclean libfclean clean fclean re tidy linux re_linux
