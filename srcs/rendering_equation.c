/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_equation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:30:18 by user              #+#    #+#             */
/*   Updated: 2022/02/18 21:00:47 by user             ###   ########.fr       */
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
    t_vec center = v_sub(ray->start, obj->obj_coord);
    hit_norm = v_sub(&hit, &center);
    l = v_sub(rt->scene->l->light_coord, ray->start);
    l = v_add(&l, &hit);
    att = ((length(l)));
    l = normalize(&l);
    hit_norm = normalize(&hit_norm);
    difuse = c_clamp(dot_p(&hit_norm, &l), 0.0, 1.0) * (0.8) * 10.0f / (att);
    return ((difuse));
}

double blinn_phong(t_frame *rt, t_ray *ray, t_obj *obj)
{
    const double shine = 1000;
    /*     const double energy_conservation = ((shine + rt->scene->l->brightness)) / (rt->scene->l->brightness * M_PI);
        printf("b%f\n", rt->scene->l->brightness);
        printf("ec%f\n", energy_conservation);
        exit(0); */
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

    if (obj->id1 == PLANE)
        return (0.0);
    if (obj->id1 == SPHERE)
        hit_norm = v_sub(&hit, &center);
    else
        return (0.0);
    // hit_norm = v_sub(&hit, &center);
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
    spec = pow(dot, shine) * (attenuation * 30);
    total = c_clamp(spec, 0.0, 1);
    return (total);
}

t_color standard_re(t_frame *rt, t_ray *ray, t_obj *obj)
{
    t_color volume;
    t_obj *current;
    float hit;
    int i = 0;
    current = rt->objs_first;
    t_ray *shadow;
    ray_init(&shadow);
    t_vec point = v_scale(rt->record.latest_t, ray->dir);
    t_vec point_p = v_3(point.x, 0, point.z);
    t_vec normal = cross_p(point, point_p);
    t_vec hit_n = v_sub(&point, &normal);
    t_vec point_to_light = v_sub(ray->start, rt->scene->l->light_coord);
    point_to_light = v_sub(&hit_n, &point_to_light);
    point_to_light = normalize(&point_to_light);
/*     print_vector(point, "point");
    print_vector(point_p, "point_p");
    print_vector(normal, "normal");
    print_vector(hit_n, "hit");
            print_vector(point_to_light, "point_to_light");
            exit(0); */
/*     point = normalize(&point);
    point_to_light = normalize(&point_to_light); */
    //t_vec norm = v_3(0, -1, 0);
    //norm = v_add(&norm, &point);
    shadow->start = ro_3(shadow, &hit_n);
    shadow->dir = rd_3(shadow, &point_to_light);
    while (++i <= rt->nbr_objs)
    {   

        hit = compute_obj(shadow, current);
        if (hit != NO_HIT && obj->id2 != current->id2)
        {
            print_vector(point, "point");
            print_vector(point_p, "point_p");
            print_vector(normal, "normal");
            print_vector(point_to_light, "point_to_l");
            exit(0);
            volume = c_grade(current->obj_color, obj->obj_color, 0, (1 / length(*(shadow->dir))));
            return (volume);
        }
        i++;
        current = current->next;
    }
    double difuse = lambert(rt, ray, obj);
    double spec = blinn_phong(rt, ray, obj);
    volume = c_grade(rt->scene->l->light_color, obj->obj_color, spec, difuse);
    return (volume);
}