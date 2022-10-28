# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 15:53:52 by jjuntune          #+#    #+#              #
#    Updated: 2022/10/20 17:03:10 by jjuntune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src/
INCLUDE_DIR = -I src/ -I include/ -I build/libsdl2/include/ -I libft/
BUILD_DIR = build/

libsdl2_makefile = libsdl2/Makefile
libsdl2_lib = $(BUILD_DIR)libsdl2/lib/libSDL2.a
libsdl2_cflags = `$(BUILD_DIR)libsdl2/bin/sdl2-config --cflags`
libsdl2_ldflags = `$(BUILD_DIR)libsdl2/bin/sdl2-config --libs`

FT_LIBRARY = libft/libft.a

SRC_FILES = $(addprefix $(SRC_DIR), main.c \
								initialize.c\
								vector_functions.c\
								vector_functions2.c\
								vector_functions3.c\
								quadratic.c\
								obj_cone.c\
								obj_cylinder.c\
								obj_plane.c\
								obj_sphere.c\
								image_render.c\
								anti_aliasing_helper.c\
								shadow.c\
								edge_detection.c\
								filters.c\
								multi_thread.c)

OBJCT_FILES = $(subst $(SRC_DIR), $(BUILD_DIR), $(SRC_FILES:.c=.o))

NAME = RT

DEPENDENCY_FILES = $(subst $(SRC_DIR), $(BUILD_DIR), $(SRC_FILES:.c=.dep))
DEPENDENCY_FLAGS = -MT $(@) -MMD -MP -MF $(BUILD_DIR)$(*).dep

LD = gcc
LDFLAGS = -flto $(libsdl2_ldflags)
CC = gcc
CFLAGS = -O3 -flto -c -Wall -Werror -Wextra -g $(addprefix -I, $(INCLUDE_DIR))\
	$(libsdl2_cflags)
CPPFLAGS = -D_REENTRANT

all: $(NAME)

$(NAME): $(FT_LIBRARY) $(OBJCT_FILES) | $(BUILD_DIR) 
	@ $(LD) $(INCLUDE_DIR) $(OBJCT_FILES) $(LDFLAGS) -o $(NAME) $(FT_LIBRARY) 

$(OBJCT_FILES): $(libsdl2_lib)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)%.o: $(SRC_DIR)%.c
$(BUILD_DIR)%.o: $(SRC_DIR)%.c | $(BUILD_DIR)%.dep
	@ $(CC) $(CFLAGS) $(CPPFLAGS) $(DEPENDENCY_FLAGS) -o $(@) $(<)

$(DEPENDENCY_FILES):

$(libsdl2_makefile):
	if test -d $(BUILD_DIR); then echo exists; else mkdir $(BUILD_DIR); fi
	cd libsdl2 && ./configure --prefix=$(abspath $(BUILD_DIR)libsdl2)\
		--disable-shared --disable-video-wayland
	$(MAKE) --directory=libsdl2

$(libsdl2_lib): $(libsdl2_makefile) | $(BUILD_DIR)
	$(MAKE) --directory=libsdl2 install

$(FT_LIBRARY):
	make -C libft/
	
clean:
	@ rm -f $(OBJCT_FILES)
	make -C libft/ clean

tidy:
	@ rm -f $(OBJCT_FILES)

new: tidy all

fclean:
	rm -f RT
	if test -f $(libsdl2_makefile); then $(MAKE) AUTOMAKE=: --directory=libsdl2\
		distclean; fi
	rm -rf $(BUILD_DIR)
	make -C libft/ fclean
	
re: fclean all

.PHONY: all clean fclean re

include $(wildcard $(DEPENDENCY_FILES))
