
#include "rtv1.h"

int ft_floor(double num)
{
	float neg;

	neg = 1;
	if (num == 0)
		return (0.0);
	if (num < 0)
	{
		neg = -1;
		num *= -1;
		if (num > 0)
			num += 1.0;
	}
	num = (int)num;
	return (num * neg);
}

/*
function spherical_map(p)
  # compute the azimuthal angle
  # -π < theta <= π
  # angle increases clockwise as viewed from above,
  # which is opposite of what we want, but we'll fix it later.
  let theta ← arctan2(p.x, p.z)

  # vec is the vector pointing from the sphere's origin (the world origin)
  # to the point, which will also happen to be exactly equal to the sphere's
  # radius.
  let vec ← vector(p.x, p.y, p.z)
  let radius ← magnitude(vec)

  # compute the polar angle
  # 0 <= phi <= π
  let phi ← arccos(p.y / radius)

  # -0.5 < raw_u <= 0.5
  let raw_u ← theta / (2 * π)

  # 0 <= u < 1
  # here's also where we fix the direction of u. Subtract it from 1,
  # so that it increases counterclockwise as viewed from above.
  let u ← 1 - (raw_u + 0.5)

  # we want v to be 0 at the south pole of the sphere,
  # and 1 at the north pole, so we have to "flip it over"
  # by subtracting it from 1.
  let v ← 1 - phi / π

  return (u, v)

 u = 0.5 + atan2(z, x) / 2π
 v = 0.5 - asin(y) / π
*/

t_vec2f get_spherical(t_obj *obj, t_vec3f rotated)
{
	t_vec2f map;
	rotated = normalize(rotated);
	map.u = (1 + atan2(rotated.z, rotated.x) / M_PI) * 0.5;
	map.v = acos(rotated.y) / M_PI;
	return (map);
}
/*
function planar_map(p)
  let u ← p.x mod 1
  let v ← p.z mod 1

  return (u, v)
end function
*/
t_vec2f	get_planar(t_vec3f rotated)
{
	return ((t_vec2f){fmod(rotated.x, 1.0), fmod(rotated.z, 1.0)});
//	return ((t_vec2f){rotated.x - ft_floor(rotated.x), rotated.z - ft_floor(rotated.z)});
}
/*
function cylindrical_map(p)
  # compute the azimuthal angle, same as with spherical_map()
  let theta ← arctan2(p.x, p.z)
  let raw_u ← theta / (2 * π)
  let u ← 1 - (raw_u + 0.5)

  # let v go from 0 to 1 between whole units of y
  let v ← p.y mod 1

  return (u, v)
  float2 toPolar(float2 cartesian){
	float distance = length(cartesian);
	float angle = atan2(cartesian.y, cartesian.x);
	return float2(angle / UNITY_TWO_PI, distance);
}
end function*/

t_vec2f	get_cylindrical(t_vec3f rotated)
{
	t_vec2f polar;

	polar.u = 1 - (atan2(rotated.x, rotated.z) / (2 * M_PI) + 0.5);
	polar.v = rotated.y - ft_floor(rotated.y);

	return (polar);
}

t_hit	*get_normal(t_obj *object, t_hit *hit)
{
	t_vec3f	temp;
	t_vec3f	temp2;
	double 	angle;
	double	len;
	t_vec3f	axis;
	t_quat	quat;

//	object->dir = normalize(object->dir);
	ft_bzero(&quat, sizeof(quat));
	ft_bzero(&axis, sizeof(axis));
	temp2 = vec_minus(hit->pos, object->pos);
	temp = temp2;
	len = vec_len(temp2);
//	temp2 = normalize(temp2);
//	temp2 = hit->pos;
//	MAKE FUNCTION TO COMPARE VECTORS TO AVOIS UNNECCESARY ROTATION
	angle = get_angle(object->dir, (t_vec3f){0.0, 1.0, 0.0});
	if (angle > 0.0)
	{
		axis = normalize(cross_product(object->dir, (t_vec3f){0.0, 1.0, 0.0}));
		quat_from_axis_angle(&axis, angle, &quat);
		quat = quat_normalize(&quat);
		quat_rotate(&quat, &temp2, &temp);
	}
	hit->rotated = temp;
	if (object->type == e_plane)
	{
		hit->surface = get_planar(temp);
		hit->normal = normalize(object->dir);
		hit->pos = vec_plus(hit->pos, vec_mult(hit->normal, BIAS));
		temp = hit->pos;
	}
	else if (object->type == e_sphere)
	{
		hit->normal = normalize(vec_minus(hit->pos, object->pos));
		hit->surface = get_spherical(object, temp);
		hit->pos = vec_plus(hit->pos, vec_mult(hit->normal, BIAS));
	}
	else if (object->type == e_cylinder)
	{
		hit->surface = get_cylindrical(temp);
		hit->normal = normalize(vec_minus(hit->pos, object->pos));
		temp = normalize(cross_product(hit->normal, object->dir));
		hit->normal = normalize(cross_product(object->dir, temp));
		hit->pos = vec_plus(hit->pos, vec_mult(hit->normal, BIAS));
	}
	else if (object->type == e_cone)
	{
		double tempy;
		t_vec3f temp_cone;

		hit->surface = get_cylindrical(temp);
		temp_cone = temp;
		hit->normal = normalize(vec_minus(hit->pos, object->pos));
		temp = normalize(cross_product(hit->normal, object->dir));
		hit->normal = normalize(cross_product(object->dir, temp));
		hit->normal.y *= object->radius / object->height;
		hit->pos = vec_plus(hit->pos, vec_mult(hit->normal, BIAS));
	}
	return (hit);
}
