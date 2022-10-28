/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:56:24 by jjuntune          #+#    #+#             */
/*   Updated: 2022/10/19 18:06:52 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef OBJECT_H
# define OBJECT_H

# include "rt.h"
# include "vector.h"


typedef union u_tuple
{
    struct 
    {
        double x;
        double y;
        double z;
        double w;
    }xyzw;
    struct
    {
        double r;
        double g;
        double b;
    }rgb;
    double a[4];
} t_tuple;
typedef t_tuple t_color;

typedef struct s_object
{
	t_vec3	loc;
	t_vec3	coi;
	t_vec3	up;
	t_vec3	rot;
	double	size;
	double	brightness;
	int		type;
	union u_tuple	color;
}	t_object;

typedef struct s_abc
{
	double		a;
	double		b;
	double		c;
}				t_abc;


#endif