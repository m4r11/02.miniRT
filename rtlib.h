/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtlib.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:15:12 by user              #+#    #+#             */
/*   Updated: 2021/11/17 19:59:06 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTLIB_H
#define RTLIB_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <float.h>

#include "libft/includes/libft.h"
#include "mlx.h"
#include "gnl.h"

typedef struct s_vec
{
    float x;
    float y;
    float z;
}t_vec;

typedef struct s_color
{
    int r;
    int b;
    int g;
    unsigned int hex;
    
}t_color;

typedef struct s_obj
{
    struct s_obj *prev;
    struct s_obj *next;
    char *raw;
    struct t_coord *obj_coord;
    struct t_color *obj_color;
    struct t_norm *obj_norm;
    float diameter;
    float height;
    

}t_obj;

typedef struct s_scene
{
    char *id;
    /* A */
    float ambient;
    struct t_color *light_color;
    /* C */
    struct t_vec *cam_coord;
    struct t_vec *cam_norm;
    int fov;
    /* L */
    struct t_vec *light_coord;
    float brightness;
    struct t_color *light_color;
}t_scene;

typedef struct s_frame
{
    char *ambient;
    char *camera;
    char *light;
    /* 🔺these are alocated separatly please 
    free after use thanks */
    struct t_scene scene;
    struct t_obj *objs_first;
    struct t_obj *objs_last;
    int nbr_objs;
}t_frame;

/* prototypes */

t_frame *init_frame(void);
t_obj *new_obj(t_frame *rt, char *data);
void add_new_obj(t_frame *rt, char *data);
void fill_scene(t_frame *rt, char id);

#endif