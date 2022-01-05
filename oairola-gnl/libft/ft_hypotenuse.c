/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hypotenuse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oairola <oairola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:38:29 by oairola           #+#    #+#             */
/*   Updated: 2021/11/29 14:07:05 by oairola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hypotenuse(int a, int b)
{
	int	hypotenuse;

	a = a * a;
	b = b * b;
	hypotenuse = ft_sqrt(a + b);
	return (hypotenuse);
}
