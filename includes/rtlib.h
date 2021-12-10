/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtlib.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldeta <mvaldeta@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:15:12 by user              #+#    #+#             */
/*   Updated: 2021/12/09 18:11:30 by mvaldeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTLIB_H
#define RTLIB_H


#define PI 3.14159265358979323846
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define BIT(x) (x * 100 / 255)
#define P(x) (x * 0.01)
#define PL(x) (x * -0.1)
#define BLACK(x) (x * -0.01)  /* change for -0.1/-0.01 for a more/less real look */
#define LIGHT(x) (x * 0.1)
#define DEC(r, g, b) (((r * 65536) + (g * 256) + b))
#define NO_HIT -33
#define WHITE 1
#define SHADE(x) (x < 0 ? PER(x) * BLACK : x * 1)
#define OBJ 8
#define BKG 9
#define SPHERE 's'
#define CYLINDER 'c'
#define PLANE 'p'

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <float.h>
#include <mlx.h>
#include <stdbool.h>

#include "mlx.h"
#include "gnl.h"
#include "libft.h"

typedef struct s_vec
{
    float x;
    float y;
    float z;
} t_vec;

typedef struct s_ray
{
    t_vec start;
    t_vec dir;
} t_ray;

typedef struct s_color
{
    int r;
    int b;
    int g;
    unsigned int hex;

} t_color;

/* mlx struct */

typedef struct s_data
{
    int line_length;    // width
    int bits_per_pixel; // bpp
    int endian;
    /* Endianness The attribute of a system that indicates whether
    integers are represented with the most significant byte
    stored at the lowest address (big endian) or at the highest address (little endian).
    Each address stores one element of the memory array. */
    int *data;
    void *img_ptr;
} t_data;

typedef struct s_obj
{
    struct s_obj *prev;
    char *raw;
    char id1;
    int id2;
    t_vec *obj_coord;
    t_color *obj_color;
    t_vec *obj_norm;
    t_vec *p;
    float diameter;
    float height;
    struct s_obj *next;

} t_obj;

typedef struct s_scene
{
    char *id;
    /* A */
    float ambient;
    t_color *amb_color;
    /* C */
    t_vec *cam_coord;
    t_vec *cam_norm;
    int fov;
    /* L */
    t_vec *light_coord;
    float brightness;
    t_color *light_color;

} t_scene;

typedef struct s_frame
{
    char *ambient;
    char *camera;
    char *light;
    /* 🔺these are alocated separatly please
    free after use thanks */
    int window_w;
    int window_h;
    t_scene *scene;
    t_obj *objs_first;
    t_obj *objs_last;
    int nbr_objs;
    void *mlx_ptr;
    void *win_ptr;
    t_data bkg_img;
    t_data obj_img;

} t_frame;

/* prototypes */

/* vector.c */
t_color c_mix(float hit, float light, t_color *obj_color);
t_color c_luminance(float alpha, t_color *color);
t_color c_blend(float alpha, t_color *color);
t_vec normalize(t_vec *p);
t_vec v_scale(float scale, t_vec *vec);
t_vec v_sub(t_vec *v1, t_vec *v2);
t_vec v_add(t_vec *v1, t_vec *v2);
t_vec v_mult(t_vec *v1, t_vec *v2);
float dot_p(t_vec *v1, t_vec *v2);

/* intersection.c */

float ray_sphere(t_ray *r, t_obj *s, t_vec obj_coord);

/* render.c */

float compute_light(t_frame *rt, t_ray *ray, t_vec obj_coord, t_color *volume);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
int render(t_frame *rt);
void general_img_to_window(t_frame *rt);
void obj_to_window(t_frame *rt);
void compute_sphere(t_obj *obj, t_frame *rt);

/* image.c */

void create_image(t_frame *rt, int which);

/* window.c */

void window_init(t_frame *rt);
void map_to_img(t_data data, int x, int y, int color);

/* ascii_to.c */

int ascii_to_int(char *data);
float ascii_to_float(char *data);
t_vec *ascii_to_vec(char *data);
t_vec *ascii_to_vec(char *data);
unsigned int ascii_to_hex(int r, int g, int b);
t_color *ascii_to_rgb(char *data);

/* create_obj.c */
t_obj *new_obj(t_frame *rt, char *data);
void add_new_obj(t_frame *rt, char *data);
void create_sphere(t_obj *obj, char *data);

/* create_scene.c */
void create_scene(t_frame *rt);
void create_objs(t_frame *rt);

/* scene.c */

t_scene *init_scene(void);

/* fill_scene.c */

t_scene *att_ambient(t_scene *scene, char **data);
t_scene *att_camera(t_scene *scene, char **data);
t_scene *att_light(t_scene *scene, char **data);
t_frame *attribute(t_frame *rt, t_scene *scene, char id, char *data);
void fill_scene(t_frame *rt, char id);

/* frame.c */

t_frame *init_frame(void);
t_frame *fill_frame(t_frame *rt);
t_frame *kill_frame(t_frame *rt);

/* parse.c */
char *parse_input(int fd);
char *save_raw(char *input);

/* minirt.c */

size_t ft_strlen(const char *str);
int minirt(void);

#endif