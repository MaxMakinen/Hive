/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 08:56:22 by mmakinen          #+#    #+#             */
/*   Updated: 2022/10/11 08:56:24 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	free_objects(t_scene *scene)
{
	t_obj	*temp;
	t_obj	*temp2;

	temp = scene->obj;
	while (temp->next != NULL)
	{
		temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
	free(temp);
}

int	open_file(int *fd, const char *filename)
{
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		ft_putendl("ERROR: failed to open file.");
		exit(0);
	}
	return (TRUE);
}

int	close_file(int fd)
{
	if (close(fd) == -1)
	{
		ft_putendl("ERROR: failed to close file");
		exit(0);
	}
	return (TRUE);
}

void	print_vec(t_vec3f *vec)
{
	printf("vec.x = %f\n", vec->x);
	printf("vec.y = %f\n", vec->y);
	printf("vec.z = %f\n", vec->z);
}

double	ft_atod(char *str)
{
	double	num;
	char	**temp;

	num = 0.0f;
	if (str)
	{
		temp = ft_strsplit(str, '.');
		if (temp && *temp)
		{
			if (temp[1])
				num = (double)ft_atoi(temp[1]) / \
				powf(10.0f, (double)ft_strlen(temp[1]));
			num += (double)ft_atoi(temp[0]);
		}
		ft_arrfree(temp);
	}
	return (num);
}
