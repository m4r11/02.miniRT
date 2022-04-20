/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:32:49 by user              #+#    #+#             */
/*   Updated: 2022/03/27 16:06:37 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

float solve_q(t_obj *o, t_vec point)
{
    float a;
    float b;
    float c;
    
    if(o->id1 == 'p')
    {
        a = o->obj_norm->x * point.x;
        b = o->obj_norm->y * point.y;
        c = o->obj_norm->z * point.z;
        return(solve_abc(a, b, c));
    }
    return(33);
}

float solve_d(t_obj *o, t_vec point)
{
    float a;
    float b;
    float c;
    float d;

    if(o->id1 == 'p')
    {
        a = o->obj_norm->x * point.x;
        b = o->obj_norm->y * point.y;
        c = o->obj_norm->z * point.z;
        d = (a + b + c);
        return (-d);
    }
    return (33);
}

float solve_abcd(float a, float b, float c, float d)
{
    return (a + b + c + d);
}

float solve_abc(float a, float b, float c)
{
    return (a + b + c);
}

t_vec normal_2p(t_vec *p1, t_vec *p2)
{
   t_vec normal = cross_p(*p1, *p2);
   return(normal);
}