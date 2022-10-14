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
				vector_math.o vector_math2.o input.o ft_bit.o ft_clamp.o \
				ft_swapf.o intersect_cone.o intersect_cylinder.o \
				intersect_sphere.o quaternion.o get_normal.o intersect_plane.o\
				shade_ray.o utility.o ft_floor.o get_surface.o rotation.o \
				input_utils.o quat_utils.o math.o ray_utils.o shade_utils.o
LIB =			libft/libft.a
MAC_LIBS =		-lmlx -lm -framework OpenGL -framework AppKit
LINUX_LIBS =	-lX11 -lXext -lmlx -lm -lpthread
INCLUDES =		-I $(INC_DIR)/ -I libft/
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

.PHONY: all libclean libfclean clean fclean re tidy linux re_linux
