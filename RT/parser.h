#ifndef PARSER_H
# define PARSER_H

# include "./libft/libft.h"
# include "./include/rt.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

//use nodex for variable size vertex lists etc?
typedef struct	s_node
{
	void			*content;
	size_t			content_size;
	struct s_node	*next;
}	t_node;

typedef struct	s_data
{
	char	***storage;
	int		nl;
	char	*nlc;
	t_object *object;
}	t_data;

#endif