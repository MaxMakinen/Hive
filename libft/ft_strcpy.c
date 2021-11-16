/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:50:40 by mmakinen          #+#    #+#             */
/*   Updated: 2021/11/15 16:07:26 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	unsigned char	pointer1;
	unsigned char	pointer2;

	pointer1 = *dst;
	pointer2 = *src;
	while (pointer2 != '\0')
	{
		pointer1++ = pointer2++;
	}
	pointer1 = pointer2;
	return (dst);
