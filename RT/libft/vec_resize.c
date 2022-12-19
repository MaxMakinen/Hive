/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_resize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 20:03:27 by jsaarine          #+#    #+#             */
/*   Updated: 2022/12/14 19:48:27 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	take in a target_size parameter and either shrink (destructively)
	or grow the vector to the target size, copying the old contents
	over to the new allocation.
*/
int	vec_resize(t_vec *src, size_t target_size)
{
	t_vec	resized;

	if (!src || !src->memory)
		return (-1);
	if (vec_new(&resized, target_size, src->elem_size) == -1)
		return (-1);
	ft_memcpy(resized.memory, src->memory, src->len * src->elem_size);
	resized.len = src->len;
	vec_free(src);
	*src = resized;
	
	return (1);
}
