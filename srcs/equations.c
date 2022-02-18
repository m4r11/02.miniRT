/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:30:11 by user              #+#    #+#             */
/*   Updated: 2022/02/18 21:05:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

float get_time_pl(t_ray *ray, t_vec *point, t_vec *normal)
{
    float time;
    float numerator;
    float denom;
    t_vec to_p;
    t_vec to_point;
    t_vec to_coord;
    t_vec n;

    to_p = v_add(ray->dir, ray->start);
    n = *normal;
    // print_vector(to_point, "where");
    to_point = *ray->dir;
    to_coord = v_sub(ray->start, point);
    // print_vector(to_point, "know");
    to_point = normalize(&to_point);
    to_coord = normalize(&to_coord);
    numerator = dot_p(&to_coord, &n);
    denom = dot_p(&to_point, &n);
    // printf("denom:%f\n", denom);
    // exit(0);
    if (denom != 0.0 && denom > 1e-6)
    {
        // printf("numerator:%f\n", numerator);
        time = (numerator / denom);
        to_p = v_scale(time, &to_p);
        float where = length(to_p);
        double is = dot_p(&to_p, &n);
        // printf("is:%f\n", (is));
   /*      printf("time:%f\n", time);
        printf("were:%f\n", where); */
        
        if ((is) > 0.0001 && where < 20)
        {
            return (where);
            //printf("is:%f\n", (is));
        }
    }
    return (NO_HIT);
}
