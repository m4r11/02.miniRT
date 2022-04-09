/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:20:57 by user              #+#    #+#             */
/*   Updated: 2022/03/27 19:36:50 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

t_parse *init_parse(void)
{
    t_parse *raw;
    raw = malloc(sizeof(t_parse));
    raw->ambient = NULL;
    raw->camera = NULL;
    raw->light = NULL;
    return(raw);
}

t_frame *init_frame(void)
{
    t_frame *rt;
    rt = malloc(sizeof(t_frame));
    rt->window_w = 520;
    rt->window_h = 340;
    rt->background = 16777215;
    rt->scene = NULL;
    rt->objs_first = NULL;
    rt->objs_last = NULL;
    rt->nbr_objs = 0;
    int i = -1;
    int j = -1;
    while(++i < rt->window_h)
    {
        while(++j < rt->window_w)
            rt->pixel_map.map[i][j] = 1;
    }
    return(rt);
}

t_camera *init_camera(void)
{ 
    t_camera  *new;
    new = malloc(sizeof(t_camera));
    new->lens = 0;
    new->h_fov = 0;
    new->v_fov = 0;
    new->focal_l = 0;
    new->cam_coord = NULL;
    new->cam_norm = NULL;
    new->m = NULL;
    return(new);
}

t_ambient *init_ambient(void)
{ 
    t_ambient  *new;
    new = malloc(sizeof(t_ambient));
    new->ambient = 0.0;
    return(new);
}
t_light *init_light(void)
{ 
    t_light  *new;
    new = malloc(sizeof(t_light));
    new->brightness = 0.0;
    new->type = 0;
    return(new);
}

t_scene *init_3dw(void)
{
    t_scene *world;
    world = NULL;
    world = malloc(sizeof(t_scene));
    world->id = 0;
    world->l = init_light();
    world->a = init_ambient();
    world->c = init_camera();   
    return(world);
}
