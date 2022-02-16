# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 10:28:04 by mmakinen          #+#    #+#              #
#    Updated: 2022/02/16 12:02:34 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =		gcc
FLAGS = 	-Wall -Wextra -Werror -o
CFLAGS =	-Wall -Wextra -Werror $(HEADER)
NAME =		fillit
SRC_PATH =	./srcs/
VPATH +=	$(SRC_PATH)
SRCS =		recu_main.c file_support.c find_tetro.c input.c t_tetro.c \
			put_tetro.c solver.c solver_support.c recursive.c
LIB =		$(SRC_PATH)libft/libft.a
OBJECTS =	$(SRCS:%.c=%.o)
HEADER =	-I $(SRC_PATH)

all: $(NAME)

$(NAME): $(OBJECTS) $(LIB)
	@$(CC) $(FLAGS) $@ $^ $(HEADER)

$(LIB):
	@make -C $(SRC_PATH)libft/

debug: $(OBJECTS) debug_libft
	@$(CC) $(FLAGS) $(NAME) -g $(OBJECTS) $(LIB) $(HEADER)

debug_libft:
	@make -C $(SRC_PATH)libft/ debug

libclean:
	@make -C $(SRC_PATH)libft/ clean

libfclean:
	rm -f $(LIB)

clean: libclean
	rm -f $(OBJECTS) 

fclean: clean libfclean
	rm -f $(NAME)

re: fclean all

tidy: all clean

.PHONY: all libclean libfclean clean fclean re tidy
