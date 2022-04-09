/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtlib.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:15:12 by user              #+#    #+#             */
/*   Updated: 2022/04/09 03:07:18 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   ifndef RTLIB_H
#   define RTLIB_H


#define PI 3.14159265358979323846
#define MAX(x, y) ((x >= y)?x:y)
#define MIN(x, y) ((x <= y)?x:y)
#define BIT(x) (x / 255)
#define CPN(x) (x / 255.00)
#define PER_TO_COLOR(x) (255 * x)
#define P(x) (x * 0.01)
#define PL(x) (x * 0.1)
#define BLACK(x) (x * -0.01)
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
#define AVOID_MAX(x) (x > 255 ? x : 255)
#define AVOID_MIN(x) (x < 0 ? x : 0)

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <float.h>
#include <stdbool.h>

#include "mlx.h"
#include "gnl.h"
#include "libft.h"
#include "bimlib.h"
#include "color.h"

typedef struct s_point
{
    float x;
    float y;
    float z;
} t_point;

typedef struct s_pixel
{
    int x;
    int y;
    
}t_pixel;

typedef struct s_pixel_map
{
    unsigned int map[3000][3000];
}t_pixel_map;

typedef struct s_vec
{
    float x;
    float y;
    float z;
} t_vec;

typedef struct s_matrix
{
    double x;
    double y;
    double z;
    double w;
} t_matrix;

typedef struct s_boxblur
{
    t_pixel m_00;
    t_pixel m_01;
    t_pixel m_02;
    t_pixel m_10;
    t_pixel m_11;
    t_pixel m_12;
    t_pixel m_20;
    t_pixel m_21;
    t_pixel m_22;
} t_boxblur;

typedef struct s_ray
{
    t_vec *start;
    t_vec *dir;
    t_vec *norm;
    float len;
} t_ray;

typedef struct s_axis
{
    t_ray up;
    t_ray side;
    t_ray rot;
    t_vec center;
    t_vec bot;
    t_vec top;
    t_vec edge;
    
}t_axis;

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
    int *data;
    void *img_ptr;
} t_data;

typedef struct s_obj
{
    struct s_obj *prev;
    struct s_obj *next;
    float diameter;
    float height;
    float spec_r;
    float shine;
    char *raw;
    char id1;
    int id2;
    float d;
    t_vec *obj_norm;
    t_vec *p;
    t_vec test;
    t_vec *obj_coord;
    t_matrix *scale;
    t_matrix *pan;
    t_matrix *hom;
    t_color *obj_color;
    t_data *img;

} t_obj;

typedef struct t_ambient
{
    float ambient;
    t_color *amb_color;
}t_ambient;

typedef struct s_light
{
    float type;
    float brightness;
    t_vec *light_coord;
    t_color *light_color;

}t_light;

typedef struct s_camera
{
    int lens;
    float h_fov;
    float v_fov;
    float focal_l;
    float a_ratio;
    t_vec *cam_coord;
    t_vec *cam_norm;
    t_matrix *m;
    t_vec clip_f;
    t_vec clip_n;
    
}t_camera;


typedef struct s_scene
{
    char *id;
    t_ambient *a;
    t_light *l;
    t_camera *c;

} t_scene;

typedef struct s_time
{
    float latest_t;
    float closest_t;
}t_time;

typedef struct s_parse
{
    char *ambient;
    char *camera;
    char *light;
}t_parse;

typedef struct s_frame
{
    void *mlx_ptr;
    void *win_ptr;
    int window_w;
    int window_h;
    int nbr_objs;
    unsigned int background;
    t_obj *objs_first;
    t_obj *objs_last;
    t_scene *scene;
    t_data bkg_img;
    t_data obj_img;
    t_time record;
    t_ray *cam_ray;
    t_ray *light_ray;
    t_ray *shadow_ray;
    t_ray *reflection_ray;
    t_pixel_map pixel_map;

} t_frame;

/* prototypes */

/* effects.c */

int limit_kernel(t_frame *rt, float source, float deviation, char xy);
t_boxblur gaussian_var(int x, int y);
unsigned int apply_blur(t_frame *rt, int x, int y);
void  depth_map(t_frame *rt, int x, int y, unsigned int pixel_color);

//int filetype_is_valid(char *arg, char *file_type);
/* lens */
float get_focal_len(float fov);

/* shapes */
float compute_obj(t_ray *ray, t_obj *obj);

t_axis gen_axis(t_obj *shape, t_ray *ray);

/* quadratics */

float solve_q(t_obj *o, t_vec p);
float solve_d(t_obj *o, t_vec p);
float solve_abcd(float a, float b, float c, float d);
float solve_abc(float a, float b, float c);

/* equations */


float get_time_pl(t_ray *ray, t_vec *point, t_vec *normal);

/* print_info */

void  print_vector(t_vec v, char *info);

/* ray */
void ray_init(t_ray **r);
// void   ray_init(t_ray **ray);
t_vec *ro_3(t_ray *ray, t_vec *where);
t_vec *rd_3(t_ray *ray, t_vec *where);
t_ray *ray_prime(t_ray *ray, t_vec *origin);
t_ray ray_from_to(t_vec *point_origin, t_vec *point_direction);

/* color */
t_color c_new_color(int r, int g, int b);
t_color c_color_components(unsigned int decimal_color);
int c_range(int d, int min, int max);
int c_increase(int max);
t_color c_mix_2colors(t_color one, t_color two);
t_color c_mix_hue(t_color onwe, t_color two, t_color hue);
float c_percentage(int color);
t_color c_isolate_hue(t_color *check);
t_color c_mix(t_frame *rt, t_color *obj, double spec, double difuse);
t_color c_grade(t_frame *rt, t_color *color, double spec, double difuse);
int c_channel_increase();

/* control */
int key_zoom(int keycode, t_frame *rt);
int	key_kill(int keycode, t_frame *rt);

/* rendering eq */
double c_clamp(double d, double min, double max);
int in_shadow(t_frame *rt, t_ray *ray, t_obj *obj);
double lambert(t_frame *rt, t_ray *ray, t_obj *obj);
double   blinn_phong(t_frame *rt, t_ray *ray, t_obj *obj);
t_color standard_re(t_frame *rt, t_ray *ray, t_obj *obj);

/* translations */
float  ndc(t_frame *rt, float coord, char id);
t_vec   world2scene(int width, int heigh, t_vec *coordinates);

/* vector.c */
t_vec normal_2p(t_vec *p1, t_vec *p2);
t_vec v_normcy(t_vec *v1);
float   degree_to_percentage(float degree);
double          angle_bet_vs(t_vec *v1, t_vec *v2);
t_vec  cross_p(t_vec a, t_vec b);
t_color c_mix_plane(float volume, float light, t_color *obj_color);
t_color c_luminance_plane(float alpha, t_color *color);
t_vec v_3(float x, float y, float z);

float v_mag(t_vec *v1, t_vec *v2);
t_color c_luminance(float alpha, t_color *color);
t_color c_blend_flat(float alpha, t_color *color);
t_color c_blend(float alpha, t_color *color);
t_vec normalize(t_vec *p);
t_vec v_scale(float scale, t_vec *vec);
t_vec v_sub(t_vec *v1, t_vec *v2);
t_vec v_from_2p(t_vec v1, t_vec v2);
t_vec v_add(t_vec *v1, t_vec *v2);
t_vec v_mult(t_vec *v1, t_vec *v2);
float dot_p(t_vec *v1, t_vec *v2);
double			length_squared(t_vec v);
double			length(t_vec v);

/* intersection.c */

float ray_sphere(t_ray *r, t_obj *s, t_vec obj_coord);
float ray_cy(t_ray *r, t_obj *p, t_vec obj_coord);
float ray_plane(t_ray *r, t_obj *p);
/* render.c */
void iterate_obj(t_frame *rt, t_ray *prime, int x, int y);
float compute_light_plane(t_frame *rt, t_ray *ray, t_vec obj_coord);
float compute_light(t_frame *rt, t_ray *ray, t_vec obj_coord);
void my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color);
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
t_color *ascii_to_rgb(char *data);
unsigned int ascii_to_hex(int r, int g, int b);

/* create_obj.c */
t_obj *new_obj(t_frame *rt, char *data);
void add_new_obj(t_frame *rt, char *data);
void create_plane(t_obj *obj, char *data);
void create_sphere(t_obj *obj, char *data);
void create_cylin(t_obj *obj, char *data);

/* create_scene.c */
void create_scene(t_parse *info, t_frame *rt);
void create_objs(t_frame *rt);

/* scene.c */

t_scene *init_3dw(void);


/* fill_scene.c */

void    fill_scene(t_parse *info, t_frame *rt, char id);
void    att_ambient(t_frame *rt, char **data);
void    att_camera(t_frame *rt, char **data);
void    att_light(t_frame *rt, char **data);
t_frame *attribute(t_frame *rt, char id, char *data);


/* frame.c */
t_frame *fill_frame(t_parse *raw, t_frame *rt);
t_frame *kill_frame(t_frame *rt);

/* parse.c */
char *parse_input(int fd);
char *save_raw(char *input);

/* init */
t_parse *init_parse(void);
t_frame *init_frame(void);
t_light *init_light(void);
t_ambient *init_ambient(void);
t_camera *init_camera(void);
t_scene *init_3dw(void);

/* free */

/* minirt.c */

size_t ft_strlen(const char *str);
int minirt(void);

#endif