# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 10:28:04 by mmakinen          #+#    #+#              #
#    Updated: 2022/05/30 11:29:40 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =			clang
FLAGS = 		-Wall -Wextra -Werror -c
DEBFLAGS = 		-Wall -Wextra -Werror -c -g
#CFLAGS += $(FLAGS)
NAME =			ft_printf.a
SRC_PATH =		./src/
VPATH =		$(SRC_PATH)
INCLUDE_PATH =	./include/ 
SRCS =			ft_printf.c flags.c conversion.c parse.c width_and_precision.c\
				ft_itoa_base_fd.c ft_bit.c
LIB =			libft.a
INCLUDES =		-I $(INCLUDE_PATH) -I ./libft/
OBJECTS =		$(addprefix $(SRC_PATH), $(SRCS:%.c=%.o))

.c.o:                            
	$(CC) $(FLAGS) $< $(INCLUDES) -o $@

all: $(NAME)

$(NAME): $(LIB) $(OBJECTS)
	ar rc $@ $(OBJECTS)

$(LIB):
	@make -C libft/
#	cp libft/libft.a ./$(NAME)

#$(OBJECTS):                                                                  
#	@$(CC) $(FLAGS) $(SRCS) $(HEADER) 

debug_objects:                                                                  
	@$(CC) $(DEBFLAGS) $(SRCS) $(HEADER) 

debug: fclean debug_libft debug_objects
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
