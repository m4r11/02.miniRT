/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_equation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldeta <mvaldeta@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:30:18 by user              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/02/17 14:54:23 by mvaldeta         ###   ########.fr       */
=======
/*   Updated: 2022/02/23 03:18:19 by user             ###   ########.fr       */
>>>>>>> normed
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

/*
Lo(x, wo) = Le(x, wo) + ∫Ω (BDRF)(LIGHT_AT_INTERSECTION)(LAMBERT), dwi
1.light out from view dir = 2.emissive light + 3.reflected light (view, all dirs)


1. position of stuff (Lo(x, wo))
Lo -> Light that leaved position of stuff
at place(x) and direction wo;

2. light radience in case hot surface.
EMISSIVE
Le -> light emmited at place etc.
Le(x, wo)

3. reflective light
integral withing unit hemisphere omega of the surface normal (preventing more light to be reflected than received
ie. conservation of energy)
and each part:
    3.1 -> BRDF :
    Lr (light radiance) unit solid-angle-in-the-direction-of-a-ray per unit projected-area-perpendicular-to-the-ray
    E  or power per unit surface area
    0i is the angle between wi and surface normal
    i is light incident
    r is reflected light
    PHONG BRDF : brdfPhong = specular_reflectance * pow(dot(R, V), shininess) * LAMBERT;
    . wi Vector 𝑅 is a direction of perfect (mirror) reflection of vector −𝐿 along the normal N
    . wo Vector 𝐿 points toward a light source, or, depending on context, specifies a direction in which
the incident ray reflects
    . n Vector 𝑁 is a shading normal for given surface (possibly coming from a normal map)
    . v Vector 𝑉, the view vector, specifies a direction from shaded point towards the viewer (camera).

    fr(wi, wr) = dLr(wr) / Li(wi)cos0i dwi
    3.2 -> LIGHT_AT_INTERSECTION
    (Li(x,wi))
    3.3 -> LAMBERT
    (wi . n)
    dot(N, L)
    the weakening factor

    To solve the integral of the rendering equation, we use a Monte-Carlo integrator.
    MONTE CARLO INTEGRATION:
        g(t) = f(t)|t1  t0|
    use random sample to make average estimation


*/
double c_clamp(double d, double min, double max)
{
    const double t = d;

    if (t < min)
        return (min);
    if (t > max)
        return (max);
    return (t);
}

int c_range(int d, int min, int max)
{
    const double t = d;

    if (t < min)
        return (min);
    if (t > max)
        return (max);
    return (t);
}

double lambert(t_frame *rt, t_ray *ray, t_obj *obj)
{
    double difuse;
    double att;
    t_vec hit;
    t_vec hit_norm;
    t_vec l;

    hit = v_scale(rt->record.latest_t, ray->dir);
    //hit = v_sub(ray->start, &hit);
    t_vec center = v_sub(ray->start, obj->obj_coord);
<<<<<<< HEAD
    hit_norm = v_sub(&hit, &center);
    if(obj->id1 == 'p')
        hit_norm = v_mult(obj->obj_norm, &hit);
    l = v_sub(ray->start, &hit);
=======
    if (obj->id1 == SPHERE)
        hit_norm = v_sub(&hit, &center);
    else
        hit_norm = *obj->obj_norm;
    l = v_sub(rt->scene->l->light_coord, ray->start);
>>>>>>> normed
    l = v_add(&l, &hit);
    //att = (length(l));
    att = (1 /length(l));
    l = normalize(&l);
    hit_norm = normalize(&hit_norm);
<<<<<<< HEAD
    difuse = c_clamp(dot_p(&hit_norm, &l) + (0.8 / (att)), 0.0, 1.0);
=======
    //difuse = c_clamp(dot_p(&hit_norm, &l) + (0.2 / (att)), 0.0, 1.0);
    difuse = c_clamp(dot_p(&hit_norm, &l), 0.0, 1.0) * (10) * (att);    
>>>>>>> normed
    return ((difuse));
}

double blinn_phong(t_frame *rt, t_ray *ray, t_obj *obj)
{
    double spec;
    double attenuation;
    double total;
    double camera;
    // double ratio;

    t_vec hit;
    t_vec hit_norm;
    t_vec v;
    t_vec l;
    t_vec h;

    hit = v_scale(rt->record.latest_t, ray->dir);
    t_vec center = v_sub(ray->start, obj->obj_coord);
    l = v_sub(rt->scene->l->light_coord, ray->start);
    l = v_add(&l, &hit);
    l = v_scale(1, &l);

    if (obj->id1 == SPHERE)
        hit_norm = v_sub(&hit, &center);
    else
        hit_norm = *obj->obj_norm;
    v = hit;
    v = normalize(&v);
    camera = length(l);
    l = normalize(&l);
    h = v_add(&v, &l);
    attenuation = 1 / camera;
    hit_norm = normalize(&hit_norm);
    h = normalize(&h);
    float dot = dot_p(&h, &hit_norm);
    if (dot < 0 || dot < 0.7)
        return (0);
    spec = pow(dot, 1000) * (attenuation) * 80;
    total = c_clamp(spec, 0.0, 1);
    return (total);
}

t_color standard_re(t_frame *rt, t_ray *ray, t_obj *obj)
{
    t_color volume;
    t_obj *current;
    float hit;
    int i = -1;
    current = rt->objs_first;
    t_ray *shadow;
   //t_color shadow_b = {0, 0, 0, 0};
    ray_init(&shadow);
<<<<<<< HEAD
    t_vec tar = v_scale(rt->record.latest_t, ray->dir);
    t_vec center = v_sub(rt->scene->l->light_coord, obj->obj_coord);
    tar = v_sub(&center, &tar);
    tar = v_scale(0.3, &tar);
    //tar = normalize(&tar);
    //t_vec l = v_add(rt->scene->l->light_coord, &tar);
    //t_vec l_dir = v_sub(&tar, &l);
    //t_vec l_dir = normalize(&l_dir);
    shadow->start = rd_3(shadow, rt->scene->l->light_coord);
    shadow->dir = ro_3(shadow, &tar);
    while (++i <= rt->nbr_objs)
    {

        hit = compute_obj(shadow, current);
        if (hit != NO_HIT && current)
        {
            break;
            /* print_vector(tar, "tar");
            print_vector(*ray->start, "from_light");
            print_vector(*ray->dir, "to_oposite");
            printf("hit:%f\n", hit);
            exit(0); */
            volume = c_grade(current->obj_color, obj->obj_color, 0, (1 / hit) * 0.3);
            // printf("shadow\n");
            return (volume);
=======
    t_vec to_hit = v_scale(rt->record.latest_t, ray->dir);
    t_vec norm = normal_2p(&to_hit, obj->obj_coord);
    //to_hit = v_scale(0.3, &to_hit);
    t_color black = {0, 0, 0, 0};
    // t_vec tar = v_scale(rt->record.latest_t, &to_hit);
    // t_vec norm = v_sub(&tar, &to_center);
    t_vec ldir = v_sub(rt->scene->l->light_coord, ray->start);
    ldir = v_add(&ldir, &to_hit);
    norm = v_scale(1, &norm);
    ldir = v_scale(-0.3, &ldir);
    //t_vec l_dir = v_3(0, 1, 0);
    //norm = normalize(&norm);
    shadow->start = ro_3(shadow, &norm);
    shadow->dir = rd_3(shadow, &ldir);
    while (++i < rt->nbr_objs)
    {

        hit = compute_obj(shadow, current);
        //printf("here");
        if (hit != NO_HIT && current)
        {
           // printf("here2");
            return (black);
>>>>>>> normed
        }
        current = current->next;
    }
    double difuse = lambert(rt, ray, obj);
    double spec = blinn_phong(rt, ray, obj);
    //difuse = 0;
    volume = c_grade(rt, obj->obj_color, spec, difuse);
    return (volume);
}