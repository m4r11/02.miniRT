/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:21:11 by mvaldeta          #+#    #+#             */
/*   Updated: 2022/05/19 09:58:44 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

void fill_scene(t_parse *raw, t_frame *rt, char id)
{
    char *data;
    if (id == 'A')
        data = raw->ambient;
    if (id == 'C')
        data = raw->camera;
    if (id == 'L')
        data = raw->light;

    attribute(rt, id, data);
    return;
}

void create_scene(t_parse *info, t_frame *rt)
{
    rt->scene = init_3dw();
    fill_scene(info, rt, 'A');
    fill_scene(info, rt, 'C');
    fill_scene(info, rt, 'L');
    return;
}

void create_objs(t_frame *rt)
{
    int i = 0;
    t_obj *current;
    current = rt->objs_first;
    while (++i <= rt->nbr_objs)
    {
        if (current->id1 == SPHERE)
            create_sphere(current, current->raw);
        if (current->id1 == PLANE)
            create_plane(current, current->raw);
        if (current->id1 == 'c')
            create_cylin(current, current->raw);
        current = current->next;
    }
    return;
}