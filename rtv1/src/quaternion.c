
#include "rtv1.h"
#include "quaternion.h"

void	quat_init(t_quat *quat)
{
    *quat = (t_quat){0.0, 0.0, 0.0, 1.0};
}

double	quat_len(t_quat *quat)
{
    return (sqrt(quat->x * quat->x + quat->y * quat->y + quat->z * quat->z + quat->w * quat->w));
}

t_quat	quat_normalize(t_quat *quat)
{
    double len;

    len = quat_len(quat);
	len = 1 / len;
    return ((t_quat){quat->x * len, quat->y * len, quat->z * len, quat->w * len});
}

t_quat	quat_conjugate(t_quat *quat)
{
    return ((t_quat){-quat->x, -quat->y, -quat->z, quat->w});
}
/*
degrees = radians × π / 180

radians =  degrees × 180 / π
*/
double rad_to_deg(double rad)
{
	return(rad * M_PI / 180);
}

double	deg_to_rad(double deg)
{
	return (deg * 180 / M_PI);
}

void	quat_from_axis_angle(t_vec3f *axis, double angle, t_quat *quat)
{
    double  temp;

	temp = sin(angle * 0.5);
	quat->w = cos(angle * 0.5);
    quat->x = axis->x * temp;
    quat->y = axis->y * temp;
    quat->z = axis->z * temp;
}

void	quat_rotate(t_quat* quat, t_vec3f *point, t_vec3f *output)
{

    double temp[10];

    temp[0] = quat->w * quat->w;
    temp[1] = quat->x * quat->x;
    temp[2] = quat->y * quat->y;
    temp[3] = quat->z * quat->z;
    temp[4] = quat->w * quat->x;
    temp[5] = quat->w * quat->y;
    temp[6] = quat->w * quat->z;
    temp[7] = quat->x * quat->y;
    temp[8] = quat->x * quat->z;
    temp[9] = quat->y * quat->z;

    // Formula from http://temp[0]w.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/transforms/index.htm
    // p2.x = w*w*p1.x + 2 * y*w*p1.z - 2 * z*w*p1.y + x*x*p1.x + 2 * y*x*p1.y + 2 * z*x*p1.z - z*z*p1.x - y*y*p1.x;
    // p2.y = 2 * x*y*p1.x + y*y*p1.y + 2 * z*y*p1.z + 2 * w*z*p1.x - z*z*p1.y + w*w*p1.y - 2 * x*w*p1.z - x*x*p1.y;
    // p2.z = 2 * x*z*p1.x + 2 * y*z*p1.y + z*z*p1.z - 2 * w*y*p1.x - y*y*p1.z + 2 * w*x*p1.y - x*x*p1.z + w*w*p1.z;

    output->x = temp[0] * point->x + 2 * temp[5] * point->z - 2 * temp[6] * point->y +
                temp[1] * point->x + 2 * temp[7] * point->y + 2 * temp[8] * point->z -
                temp[3] * point->x - temp[2] * point->x;
    output->y = 2 * temp[7] * point->x + temp[2] * point->y + 2 * temp[9] * point->z +
                2 * temp[6] * point->x - temp[3] * point->y + temp[0] * point->y -
                2 * temp[4] * point->z - temp[1] * point->y;
    output->z = 2 * temp[8] * point->x + 2 * temp[9] * point->y + temp[3] * point->z -
                2 * temp[5] * point->x - temp[2] * point->z + 2 * temp[4] * point->y -
                temp[1] * point->z + temp[0] * point->z;
}

void quat_multiply(t_quat* q1, t_quat* q2, t_quat* output)
{
    /*
    Formula from http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/arithmetic/index.htm
             a*e - b*f - c*g - d*h
        + i (b*e + a*f + c*h- d*g)
        + j (a*g - b*h + c*e + d*f)
        + k (a*h + b*g - c*f + d*e)
    */
    output->w = q1->w * q2->w - q1->x * q2->x - q1->y*q2->y - q1->z*q2->z;
    output->x = q1->x * q2->w + q1->w * q2->x + q1->y*q2->z - q1->z*q2->y;
    output->y = q1->w * q2->y - q1->x * q2->z + q1->y*q2->w + q1->z*q2->x;
    output->z = q1->w * q2->z + q1->x * q2->y - q1->y*q2->x + q1->z*q2->w;
}