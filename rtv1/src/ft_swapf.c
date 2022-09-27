#include "rtv1.h"

void	ft_swapf(double *a, double *b)
{
	double c;

	c = *a;
	*a = *b;
	*b = c;
}