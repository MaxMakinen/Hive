# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 10:28:04 by mmakinen          #+#    #+#              #
#    Updated: 2022/05/30 14:35:37 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =			clang
FLAGS = 		-Wall -Wextra -Werror -c
DEBFLAGS = 		-Wall -Wextra -Werror -c -g
NAME =			libftprintf.a
SRC_PATH =		./src/
INCLUDE_PATH =	./include/ 
SRCS =			ft_printf.c flags.c conversion.c parse.c width_and_precision.c\
				ft_itoa_base_fd.c ft_bit.c get_number.c
LIB =			libft.a
INCLUDES =		-I $(INCLUDE_PATH) -I ./libft/
OBJECTS =		$(addprefix $(SRC_PATH), $(SRCS:%.c=%.o))
DEBOBJ =		$(addprefix $(SRC_PATH), $(SRCS:%.c=%.o))

.c.o:                            
	@$(CC) $(FLAGS) $< $(INCLUDES) -o $@

all: $(NAME)

$(NAME): $(LIB) $(OBJECTS)
	cp libft/libft.a ./$(NAME)
	ar rc $@ $(OBJECTS)
	ranlib $(NAME)

$(LIB):
	@make -C libft/

#	Doesn't work
debug: fclean debug_libft $(DEBOBJ)
	@$(CC) $(FLAGS) -o $(NAME) -g $(OBJECTS) $(LIB) $(INCLUDES)

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

tidy: all clean

.PHONY: all libclean libfclean clean fclean re tidy
