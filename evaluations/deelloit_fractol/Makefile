# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/02 14:45:22 by deelliot          #+#    #+#              #
#    Updated: 2022/09/07 10:43:37 by deelliot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

FLAGS = -Wall -Wextra -Werror -g

# Directories
SRC_DIR = ./srcs/
OBJ_DIR = ./obj/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/

# Source and object files
SRCS = 1_main.c
SRCS += 2_initialise.c
SRCS += 3_threads.c
SRCS += 4_plot.c
SRCS += 5_fractal.c
SRCS += 5_multibrot.c
SRCS += 5_barnsley_fern.c
SRCS += 6_image.c
SRCS += 7_mouse_input.c
SRCS += 7_key_input.c
SRCS += 8_menu.c
SRCS += 9_error_handling.c

OBJ_FILES = $(SRCS:.c=.o)

# Paths
SRC = $(addprefix $(SRC_DIR), $(SRCS))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

# Libraries
LINKS =  -L $(LIBFT_DIR) -lft
LINKS += -L /usr/local/lib -lmlx -I /usr/local/include -framework \
	OpenGL -framework AppKit

#Rules
all: obj $(LIBFT) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@gcc $(FLAGS) -I $(LIBFT_DIR) -I $(INC_DIR) -o $@ -c $<
$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@clear
	@echo "***** Compiling *****"
	@sleep 1
	@clear
	@echo "***** Compiling *****"
	@sleep 1
	@gcc $(OBJ) $(LINKS) -lm -o $(NAME)
	@clear
	@echo "***** $(NAME) generated *****"
	@echo
	@echo "Usage: ./fractol + option"
	@echo "options: >> julia"
	@echo "options: >> mandelbrot"
	@echo "options: >> multibrot"
	@echo "options: >> multijulia"
	@echo "options: >> tricorn"
	@echo "options: >> burningship"
	@echo "options: >> barnsleyfern"

clean:
	@rm -Rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo " Objects removed"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo " $(NAME) removed "

re: fclean all

.PHONY: all clean fclean re