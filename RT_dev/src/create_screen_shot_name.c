/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_screen_shot_name.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:36:25 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/07 13:42:24 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

char	*create_screen_shot_name(char *image_name, int image_nbr)
{
	char		*temp;

	image_name = ft_itoa(image_nbr++);
	if (image_name == NULL)
		return (NULL);
	temp = ft_strjoin("./Images/screen_shot_", image_name);
	ft_strdel(&image_name);
	if (temp == NULL)
		return (NULL);
	image_name = ft_strjoin(temp, ".ppm");
	if (image_name == NULL)
		return (NULL);
	ft_strdel(&temp);
	return (image_name);
}
