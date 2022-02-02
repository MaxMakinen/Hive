# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 10:28:04 by mmakinen          #+#    #+#              #
#    Updated: 2022/02/01 16:09:36 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =		gcc
FLAGS = 	-Wall -Wextra -Werror -o
DEBFLAGS = 	-Wall -Wextra -Werror -g -c
NAME =		fillit
SRC_PATH =	./
INCLUDE =	./
SRCS =		iter_main.c file_support.c find_tetro.c input.c t_tetro.c \
			put_tetro.c iterative.c
R_SRCS =	recu_main.c file_support.c find_tetro.c input.c t_tetro.c \
			put_tetro.c
LIB =		libft/libft.a
OBJECTS =	$(SRCS:.c=.o)
R_OBJECTS =	$(R_SRCS:.c=.o)
HEADER =	-I $(INCLUDE)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS) $(NAME) $(OBJECTS) $(LIB) $(HEADER)

recursive: $(R_OBJECTS)
	$(CC) $(FLAGS) $(NAME) $(R_OBJECTS) $(LIB) $(HEADER)

debug_objects:
	@$(CC) $(DEBFLAGS) $(SRCS) $(HEADER)

r_debug_objects:
	@$(CC) $(DEBFLAGS) $(R_SRCS) $(HEADER)

debug_file: debug_objects
	@$(CC) $(FLAGS) $(NAME) -g $(OBJECTS) $(LIB) $(HEADER)

r_debug_file: r_debug_objects
	@$(CC) $(FLAGS) $(NAME) -g $(R_OBJECTS) $(LIB) $(HEADER)

debug_libft:
	@make -C libft/ debug

debug: fclean debug_libft debug_file

debug_recursive: fclean debug_libft r_debug_file

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

tidy: all clean

.PHONY: all clean fclean re tidy debug debug_recursive debug_libft r_debug_file\
		debug_file r_debug_objects debug_objects recursive
