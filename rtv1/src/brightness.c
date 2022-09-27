/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brightness.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:58:05 by mmakinen          #+#    #+#             */
/*   Updated: 2022/08/31 14:46:51 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_rgb	color_mult(t_rgb color, double num)
{
	color.rgb[0] *= num;
	color.rgb[1] *= num;
	color.rgb[2] *= num;
//	color.rgb[3] *= num;
	return (color);
}

t_rgb	mix(t_rgb color, t_rgb color2, double mix_value)
{
	color = color_mult(color, 1 - mix_value);
	color2 = color_mult(color2, mix_value);
	color.rgb[0] += color2.rgb[0];
	color.rgb[1] += color2.rgb[1];
	color.rgb[2] += color2.rgb[2];

	return (color);
}

/*
function uv_pattern_at(checkers, u, v)
  let u2 ← floor(u * checkers.width)
  let v2 ← floor(v * checkers.height)

 if (u2 + v2) mod 2 == 0 then
   return checkers.color_a
 else
   return checkers.color_b
 end if
end function

           auto sines = sin(10*p.x())*sin(10*p.y())*sin(10*p.z());
            if (sines < 0)
                return odd->value(u, v, p);
            else
                return even->value(u, v, p);
*/
t_rgb	pattern_at(t_pattern pattern, t_vec2f map)
{
	int u2;
	int	v2;

	u2 = ft_floor(map.u * pattern.width);
	v2 = ft_floor(map.v * pattern.height);
	if ((u2 + v2) % 2 == 0)
		return (pattern.color1);
	else
		return (pattern.color2);
}
/*
fixed4 frag(v2f i) : SV_TARGET{
    //add different dimensions
    float chessboard = floor(i.worldPos.x) + floor(i.worldPos.y);
    //divide it by 2 and get the fractional part, resulting in a value of 0 for even and 0.5 for odd numbers.
    chessboard = frac(chessboard * 0.5);
    //multiply it by 2 to make odd values white instead of grey
    chessboard *= 2;
    return chessboard;

	virtual color value(double u, double v, const point3& p) const override {
            auto sines = sin(10*p.x())*sin(10*p.y())*sin(10*p.z());
            if (sines < 0)
                return odd->value(u, v, p);
            else
                return even->value(u, v, p);
	*/
t_rgb	pattern_3dgrid(t_pattern pattern, t_hit *hit)
{
	double	grid;
	t_vec3f	point;

//	point = vec_minus(hit->rotated, hit->obj->pos);
	point = hit->pos;
	point = vec_div(point, (pattern.width + pattern.height) / 2.0);

//	if (ft_floor(point.y))
//		printf("POINT Y FLOOR = %d\nPOINT X = %f\nPOINT Y= %f\nPOINT Z = %f\n", ft_floor(point.y), point.x, point.y, point.z);
	grid = sin(10 * point.x) * sin(10 * point.y) * sin(10 * point.z);
//	grid = ft_floor(point.x) + ft_floor(point.z) + ft_floor(point.y);
//	grid = ft_floor(hit->pos.x) + ft_floor(hit->pos.y) + ft_floor(hit->pos.z);
//	grid *= 0.5;
//	grid -= (int)grid;
//	grid *= 2;
//	if ((int)grid % 2 == 0)
	if (grid < 0)
		return (pattern.color1);
	else
		return (pattern.color2);
}

t_rgb	pattern_checkerboard_plane(t_pattern pattern, t_hit *hit)
{
	double	grid;
	t_vec3f	point;

	point = hit->rotated;
	point = vec_div(point, (pattern.width + pattern.height) / 2.0);
	grid = ft_floor(point.x) + ft_floor(point.z);
	grid *= 0.5;
	grid -= (int)grid;
	grid *= 2;
	if ((int)grid % 2 == 0)
		return (pattern.color1);
	else
		return (pattern.color2);
}

void	norm_dot_color(t_data *data, t_vec3f *light, int x, int y, t_hit *hit)
{
	t_vec3f		lightpos;
	double		angle;
	double		scale = 4;
	double		pattern;
	t_pattern	checkers;
	t_pattern	grid;
	t_pattern	cylinder;
	t_rgb		color;

	color = hit->obj->color;
	checkers = (t_pattern){4.0 * hit->obj->radius, 2.0 * hit->obj->radius, color, color_mult(color, 0.8)};
	grid = (t_pattern){2, 2, color, color_mult(color, 0.8)};
	cylinder = (t_pattern){10.0 * hit->obj->radius, 2, color, color_mult(color, 0.8)};
	lightpos = normalize(vec_minus(*light, hit->pos));
	angle = ft_clamp(dot_product(hit->normal, lightpos), 0.0, 1.0);
	if (hit->obj->type == e_sphere)
		color = pattern_at(checkers, hit->surface);
	if (hit->obj->type == e_plane)
		color = pattern_at(grid, hit->surface);
	if (hit->obj->type == e_cylinder || hit->obj->type == e_cone)
	{
		color = pattern_at(cylinder, hit->surface);
	}
	color.rgb[0] *= angle;
	color.rgb[1] *= angle;
	color.rgb[2] *= angle;		
	data->map.ptr[y][x] = color.color;
}
 
 //       float pattern = (fmodf(hit->surface.x * scale, 1) > 0.5) ^ (fmodf(hit->surface.y * scale, 1) > 0.5); 
 //       hitColor = mix(hitObject->color, hitObject->color * 0.8, pattern); 
