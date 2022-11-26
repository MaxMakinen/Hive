#include "../include/tuple.h"
#include "../include/object.h"
#include "../include/rt.h"
#include <stddef.h>

  t_color   shade_hit(t_scene *scene, t_hit_record *hit)
{
  t_color result;
  t_color temp;
  t_light light;
  size_t  i;

  i = 0;
  result = color_new(0,0,0);
  while (i < scene->lights.len)
  {
    light = *(t_light *)vec_get(&scene->lights, i);
    temp = lighting(hit->object->material, light, hit->hit_loc, hit->to_eye, hit->normal);
    result = tuple_add(result, temp);
	i++;
  }



  return (result);
}


