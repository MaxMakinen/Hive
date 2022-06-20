# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 10:28:04 by mmakinen          #+#    #+#              #
#    Updated: 2022/06/19 12:43:49 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =			clang
NAME =			libftprintf.a
SRC_PATH =		./src/
INCLUDE_PATH =	./include/ 
SRCS =			ft_printf.c flags.c conversion.c unsigned_conversion.c \
				parse.c width_and_precision.c ft_ulltoa_base_fd.c ft_bit.c \
				get_number.c print_padding.c print_float.c
LIB =			libft.a
FLAGS = 		-Wall -Wextra -Werror -c $(CFLAGS) -g
CPPFLAGS =		-I $(INCLUDE_PATH) -I ./libft/
OBJECTS =		$(addprefix $(SRC_PATH), $(SRCS:%.c=%.o))

.c.o:                            
	@$(CC) $(FLAGS) $< $(CPPFLAGS) -o $@

all: $(NAME)

$(NAME): $(LIB) $(OBJECTS)
	cp libft/libft.a ./$(NAME)
	ar rc $@ $(OBJECTS)
	ranlib $(NAME)

$(LIB):
	@make -C libft/

#	Doesn't work
debug: fclean debug_libft
	make CFLAGS="-g"

debug_libft:
	@make -C libft/ debug

libclean:
	@make -C libft/ clean

libfclean:
	@make -C libft/ fclean

clean: libclean
	rm -f $(OBJECTS) 

fclean: clean libfclean
	rm -f $(NAME)

re: fclean all

tidy: re clean
	rm -f $(OBJECTS) 

.PHONY: all libclean libfclean clean fclean re tidy
