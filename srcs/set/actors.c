/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:32:20 by user              #+#    #+#             */
/*   Updated: 2022/02/21 16:33:45 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

t_obj *new_obj(t_frame *rt, char *data)
{
    t_obj *new = NULL;

    new = malloc(sizeof(t_obj));
    printf("data in <data> new obj: %s\n", data);
    new->raw = malloc(ft_strlen(data) + 1);
    ft_strlcpy(new->raw, data, ft_strlen(data));
    new->prev = NULL;
    new->next = NULL;
    new->id1 = new->raw[0];
    new->id2 = rt->nbr_objs;
    new->obj_coord = NULL;
    new->p = NULL;
    new->obj_color = NULL;
    new->obj_norm = NULL;
    new->diameter = 0;
    new->height = 0;
    rt->nbr_objs++;
    return (new);
}

void add_new_obj(t_frame *rt, char *data)
{
    t_obj *new = NULL;
    t_obj *old_tail = NULL;
    char *input = NULL;


    input = malloc(ft_strlen(data) + 1);
    ft_strlcpy(input, data, ft_strlen(data) + 1);
    new = new_obj(rt, input);
    free(input);
    
    if(rt->objs_first == NULL)
    {
        rt->objs_first = new;
        rt->objs_last = new;
        rt->objs_first->prev = NULL;
        rt->objs_first->next = rt->objs_last;
        rt->objs_last->prev = rt->objs_first;
        return;
    }

    old_tail = rt->objs_last;
    new->prev = old_tail;
    new->next = NULL;
    old_tail->next = new;
    old_tail->prev = old_tail->prev->next;
    rt->objs_last = new;
    rt->objs_last->prev = new->prev;
    return;
}

void create_plane(t_obj *obj, char *data)
{
    char **plane;
    plane = ft_split(data, ' ');

    obj->id1 = 'p';
    obj->obj_coord = ascii_to_vec(plane[1]);
    obj->obj_norm = ascii_to_vec(plane[2]);
    obj->obj_color = ascii_to_rgb(plane[3]);
    obj->d = solve_d(obj, *obj->obj_coord);
    //printf("d:%f\n", obj->d);
    //exit(0);
 /*    printf("d:%f\n", obj->d);
    printf("p:%c\n", obj->id1);
    exit(0); */
/*     print_vector(*obj->obj_norm, "norm");
    printf("d:%f\n", d);
    exit(0); */
/*     print_vector(normal, "norm");
    print_vector(*obj->obj_norm, "ptrnorm"); */
    //exit(0);
/*     print_vector(normal, "norm");
    print_vector(*obj->obj_norm, "ptrnorm");
    exit(0); */
}

void create_sphere(t_obj *obj, char *data)
{
    char **sphere;
    sphere = ft_split(data, ' ');

    obj->id1 = 's';
    obj->obj_coord = ascii_to_vec(sphere[1]);
    obj->diameter = ascii_to_float(sphere[2]);
    obj->obj_color = ascii_to_rgb(sphere[3]);
}

void create_cylin(t_obj *obj, char *data)
{
    char **cylin;
    cylin = ft_split(data, ' ');

    obj->id1 = 'c';
    obj->obj_coord = ascii_to_vec(cylin[1]);
    obj->obj_norm = ascii_to_vec(cylin[2]);
    obj->diameter = ascii_to_float(cylin[3]);
    obj->height = ascii_to_float(cylin[4]);
    obj->obj_color = ascii_to_rgb(cylin[5]);
}

