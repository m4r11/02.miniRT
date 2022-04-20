/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:50:22 by user              #+#    #+#             */
/*   Updated: 2022/03/09 21:14:42 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

t_vec normalize(t_vec *v)
{
    t_vec p;
    p = v_3(v->x,v->y,v->z);
    float w = length(*v);
    //printf("LEN%f\n", w);
    p.x /= w;
    p.y /= w;
    p.z /= w;
    return (p);
}

t_vec v_scale(float scale, t_vec *vec)
{
    t_vec new;

    new.x = vec->x *scale;
    new.y = vec->y *scale;
    new.z = vec->z *scale;

    return (new);
}

float v_mag(t_vec *v1, t_vec *v2)
{
    float x = (v2->x - v1->x) * (v2->x - v1->x);
    float y = (v2->y - v1->y) * (v2->y - v1->y);
    float z = (v2->z - v1->z) * (v2->z - v1->z);
    float magnitude = sqrtf(x + y + z);
    return (magnitude);
}

t_vec cross_p(t_vec a, t_vec b)
{
    t_vec cross;

    cross.x = a.x * b.z - a.z * b.y;
    cross.y = a.z * b.x - a.x * b.z;
    cross.z = a.x * b.y - a.y * b.x;

    return (cross);
}

t_vec v_sub(t_vec *v1, t_vec *v2)
{
    t_vec new;

    new.x = v2->x - v1->x;
    new.y = v2->y - v1->y;
    new.z = v2->z - v1->z;
    return (new);
}

t_vec v_from_2p(t_vec start, t_vec end)
{
    t_vec vector;
    vector = v_sub(&end, &start);
    vector.x = sqrtf(vector.x * vector.x);
    vector.y = sqrtf(vector.y * vector.y);
    vector.z = sqrtf(vector.z * vector.z);
    return (vector);
}

t_vec v_add(t_vec *v1, t_vec *v2)
{
    t_vec new;
    // exit(0);
    new.x = v1->x + v2->x;
    new.y = v1->y + v2->y;
    new.z = v1->z + v2->z;

    return (new);
}

t_vec v_mult(t_vec *v1, t_vec *v2)
{
    t_vec new;

    new.x = v1->x * v2->x;
    new.y = v1->y * v2->y;
    new.z = v1->z * v2->z;

    return (new);
}

t_vec v_normcy(t_vec *v1)
{
    t_vec new;

    new.x = v1->x * 2;
    new.y = v1->y * 0;
    new.z = v1->z * 2;

    return (new);
}

t_vec v_3(float x, float y, float z)
{
    t_vec new;
    new.x = x;
    new.y = y;
    new.z = z;
    return(new);
}

t_vec *ro_3(t_ray *ray, t_vec *where)
{
    //exit(0);
    ray->start->x = where->x;
    ray->start->y = where->y;
    ray->start->z = where->z;
    return(ray->start);
}

t_vec *rd_3(t_ray *ray, t_vec *where)
{
    ray->dir->x = where->x;
    ray->dir->y = where->y;
    ray->dir->z = where->z;
    return(ray->dir);
}

float dot_p(t_vec *v1, t_vec *v2)
{
    float dot;
    float a;
    float b;
    float c;

    a = v1->x * v2->x;
    b = v1->y * v2->y;
    c = v1->z * v2->z;
    /*
        printf("**********DOT**********\n");
        printf("v1x:%f\n", v1->x);
        printf("v1y:%f\n", v1->y);
        printf("v1z:%f\n", v1->z);

        printf("a:%f\n", a);
        printf("b:%f\n", b);
        printf("c:%f\n", c); */

    dot = a + b + c;
    // printf("dot:%f\n", dot);
    return (dot);
}

static double sqr(double n)
{
    return (n * n);
}

double length_squared(t_vec v)
{
    return (sqr(v.x) + sqr(v.y) + sqr(v.z));
}

double length(t_vec v)
{
    return (sqrt(length_squared(v)));
}

double angle_bet_vs(t_vec *v1, t_vec *v2)
{
    float scalar = dot_p(v1, v2);
    float mag1 = length(*v1);
    float mag2 = length(*v2);
    float angle = scalar / (mag1 * mag2);
    // printf("angle should be between 0 & 180: %f\n", acos(angle));
    return (acos(angle));
}

