/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:42:42 by user              #+#    #+#             */
/*   Updated: 2022/02/23 11:38:39 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

/* t_trans *relationashiop_transform(t_vec *pos, t_frame *rt)
{
    t_trans *ret;
    
    ret->cam_matrix.p_x = rt->window_w / 2;
    ret->cam_matrix.p_y = rt->window_h / 2;
    ret->cam_matrix.n_x = (rt->window_w / 2) * -1;
    ret->cam_matrix.n_y = (rt->window_h / 2) * -1;

    ret->cam_in_3dworld = pos;
    ret->anything_to_screen = 
} */

float  ndc(t_frame *rt, float coord, char id)
{
    float aspect_ratio = (double)rt->window_w / (double)rt->window_h;
    rt->scene->c->v_fov = rt->scene->c->h_fov / aspect_ratio;
/*     printf("VFOV:%f\n", rt->scene->c->v_fov);
    printf("HFOV:%f\n", rt->scene->c->h_fov);
    exit(0); */
    if(id == 'x')
        coord = (2 * ((coord + 0.5) / rt->window_w) -1) * atan((rt->scene->c->h_fov / 2) * (M_PI / 180)) * aspect_ratio;
    if(id == 'y')
       coord = (1 - 2 * (coord + 0.5) / rt->window_h) * atan((rt->scene->c->v_fov / 2) * (M_PI / 180)) * aspect_ratio;
    if(id == 'z')
        return(rt->scene->c->cam_norm->z);
    return(coord);
}

/* t_vec ray(t_vec coord1, t_vec coord2)
{
    
} */