# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 10:28:04 by mmakinen          #+#    #+#              #
#    Updated: 2022/02/07 17:29:15 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =		gcc
FLAGS = 	-Wall -Wextra -Werror -o
DEBFLAGS = 	-Wall -Wextra -Werror -g -c
CFLAGS =	-Wall -Wextra -Werror -g $(HEADER)
NAME =		fillit
SRC_PATH =	./srcs/
VPATH =		$(SRC_PATH)
INCLUDE =	./include/
SRCS =		recu_main.c file_support.c find_tetro.c input.c t_tetro.c \
			put_tetro.c solver.c recursive.c
LIB =		$(SRC_PATH)libft/libft.a
OBJECTS =	$(SRCS:.c=.o)
IT_OBJECTS =	$(IT_SRCS:.c=.o)
HEADER =	-I $(INCLUDE)

all: makelib $(NAME)

makelib:
	@make -C $(SRC_PATH)libft/

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS) $@ $^ $(LIB) $(HEADER)

debug: $(OBJECTS)
	$(CC) $(FLAGS) $(NAME) -g $^ $(LIB) $(HEADER)

iterative: $(IT_OBJECTS)
	$(CC) $(FLAGS) $(NAME) $(OBJECTS) $(LIB) $(HEADER)

it_debug_objects:
	@$(CC) $(DEBFLAGS) $(IT_SRCS) $(HEADER)

debug_objects:
	$(CC) $(DEBFLAGS) $(SRCS) $(HEADER)

it_debug_file: it_debug_objects
	@$(CC) $(FLAGS) $(NAME) -g $(IT_OBJECTS) $(LIB) $(HEADER)

debug_file: debug_objects
	@$(CC) $(FLAGS) $(NAME) -g $(OBJECTS) $(LIB) $(HEADER)

debug_libft:
	@make -C $(SRC_PATH)libft/ debug

#debug: fclean debug_libft debug_file

debug_recursive: fclean debug_libft it_debug_file

libclean:
	@make -C $(SRC_PATH)libft/ clean


libfclean:
	@make -C $(SRC_PATH)libft/ fclean

clean: libclean
	rm -f *.o 

fclean: libfclean clean
	rm -f $(NAME)

re: fclean all

tidy: all clean

.PHONY: all clean fclean re tidy debug debug_recursive debug_libft r_debug_file\
		debug_file r_debug_objects debug_objects recursive
