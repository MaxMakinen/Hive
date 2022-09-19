#include "rtv1.h"

void	ft_swapf(float *a, float *b)
{
	float c;

	c = *a;
	*a = *b;
	*b = c;
}