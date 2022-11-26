/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 13:01:00 by jsaarine          #+#    #+#             */
/*   Updated: 2022/11/06 13:17:31 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H
# include <stddef.h>

typedef struct s_vec
{
	void	*memory;
	size_t	elem_size;
	size_t	alloc_size;
	size_t	len;
}			t_vec;

int			vec_new(t_vec *src, size_t init_len, size_t elem_size);
void		vec_free(t_vec *src);
int			vec_from(t_vec *dst, void *src, size_t len, size_t elem_size);
int			vec_resize(t_vec *src, size_t target_size);
int			vec_push(t_vec *src, void *elem);
int			vec_append(t_vec *dst, t_vec *src);
void		*vec_get(t_vec *src, size_t index);

#endif