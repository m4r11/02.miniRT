/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 20:02:38 by user              #+#    #+#             */
/*   Updated: 2022/02/23 00:21:45 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

void ray_init(t_ray **r)
{
   *r = malloc(sizeof(t_ray));
    (*r)->start = malloc(sizeof(t_vec));
    (*r)->dir = malloc(sizeof(t_vec));
    (*r)->norm = malloc(sizeof(t_vec));
    (*r)->len = 0;
}

t_ray *ray_prime(t_ray *ray, t_vec *origin)
{
    ray_init(&ray);
    ray->start->x = origin->x;
    ray->start->y = origin->y;
    ray->start->z = origin->z;
    return(ray);
}

t_ray ray_from_to(t_vec *point_origin, t_vec *point_direction)
{
    t_ray *new;
    ray_init(&new);
    *new->start = v_3(point_origin->x, point_origin->y, point_origin->z);
    *new->dir = v_3(point_direction->x, point_direction->y, point_direction->z);
    *new->norm = normalize(new->dir);
    new->len = length(*new->dir);
    return(*new);
}

t_ray ray_shadow(t_vec *point_origin, t_vec *point_direction)
{
    t_ray *new;
    ray_init(&new);
    *new->start = v_3(point_origin->x, point_origin->y, point_origin->z);
    *new->dir = v_3(point_direction->x, point_direction->y, point_direction->z);
    *new->norm = normalize(new->dir);
    new->len = length(*new->dir);
    return(*new);
}

/* t_vec ray_time(t_vec point_origin, t_vec point_direction)
{

}

t_vec ray_invert_direction(t_vec point_origin, t_vec point_direction)
{

} */