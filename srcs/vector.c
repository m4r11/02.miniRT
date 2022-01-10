/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:50:22 by user              #+#    #+#             */
/*   Updated: 2022/01/10 01:09:03 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

t_vec normalize(t_vec *p)
{
    float w = sqrtf(p->x * p->x + p->y * p->y + p->z * p->z);
    p->x /= w;
    p->y /= w;
    p->z /= w;
    return (*p);
}

t_color c_mix(float volume, float light, t_color *obj_color)
{
    t_color model;
    t_color shaded;

    model = c_blend(volume, obj_color);
    shaded = c_luminance(light, &model);
    return (shaded);
}

t_color c_mix_plane(float volume, float light, t_color *obj_color)
{
    t_color model;
    t_color shaded;

    model = c_blend_flat(volume, obj_color);
    shaded = c_luminance_plane(light, &model);
    return (shaded);
}

t_color c_blend_flat(float alpha, t_color *color)
{
    t_color new;

    new.r = MIN(PL(alpha), 0.99) * color->r;
    new.g = MIN(PL(alpha), 0.99) * color->g;
    new.b = MIN(PL(alpha), 0.99) * color->b;
    /*
        printf("in BLEND color R: %u\n", color->r);
        printf("in BLEND color G: %u\n", color->g);
        printf("in BLEND color B: %u\n", color->b);

        printf("NEW BLEND R: %u\n", new.r);
        printf("NEW BLEND G: %u\n", new.g);
        printf("NEW BLEND B: %u\n", new.b); */

    new.hex = DEC(new.r, new.g, new.b);
    return (new);
}

/* t_color c_blend(float alpha, t_color *color)
{
    t_color new;

    printf("ALPHA: %f\n", alpha);
    printf("ALPHA: %f\n", alpha);
    if(alpha < 0)
        alpha  = 1;
    new.r = MIN(alpha + CPN(color->r), 1) * 255;
    new.g = MIN(alpha + CPN(color->g), 1) * 255;
    new.b = MIN(alpha + CPN(color->b), 1) * 255;

    printf("BLEND R: %u\n", new.r);
    printf("BLEND G: %u\n", new.g);
    printf("BLEND B: %u\n", new.b);

    new.hex = DEC(new.r, new.g, new.b);
    return (new);
} */

float degree_to_percentage(float degree)
{
    float percentage = (degree);
    return (percentage);
}

t_color c_blend(float alpha, t_color *color)
{
    t_color new;
    alpha = P(alpha);
    printf("ALPHA IN BLEND: %f\n", alpha);

    new.r = MIN(alpha + CPN(color->r), 1) * 255;
    new.g = MIN(alpha + CPN(color->g), 1) * 255;
    new.b = MIN(alpha + CPN(color->b), 1) * 255;

    /*     printf("PR: %f\n", CPN(color->r));
        printf("PG: %f\n", CPN(color->g));
        printf("PB: %f\n", CPN(color->b));
        exit(0); */

    new.hex = DEC(new.r, new.g, new.b);
    return (new);
}

t_color c_luminance(float alpha, t_color *color)
{
    t_color new;
    if (alpha < 0)
    {
        new.r = 0;
        new.g = 255;
        new.b = 0;
        new.hex = DEC(new.r, new.g, new.b);
        return (new);
    }

    new.r = MIN((alpha)*color->r, 255);
    new.g = MIN((alpha)*color->g, 255);
    new.b = MIN((alpha)*color->b, 255);

    /*     printf("PR: %f\n", CPN(color->r));
        printf("PG: %f\n", CPN(color->g));
        printf("PB: %f\n", CPN(color->b));
        exit(0); */

    new.hex = DEC(new.r, new.g, new.b);
    return (new);
}

t_color c_luminance_plane(float alpha, t_color *color)
{
    t_color final;

    // printf("ALPHA: %f\n", alpha);
    // printf("ALPHA QUANTIY: %f\n", (PL2(alpha)));

    /*     if(alpha == 0)
            alpha = 0.2;
     */
    alpha = P(BIT(alpha));
    printf("ALPHA: %f\n", alpha);
    final.r = MIN(alpha, 0.9) * color->r;
    final.g = MIN(alpha, 0.9) * color->g;
    final.b = MIN(alpha, 0.9) * color->b;
    printf("color R: %u\n", final.r);
    printf("color G: %u\n", final.g);
    printf("color B: %u\n", final.b);
    // printf("\t PERCENTAGE - ALPHA IN FLAT LUM %f\n", alpha);
    /*
        printf("color R: %u\n", color->r);
        printf("color G: %u\n", color->g);
        printf("color B: %u\n", color->b); */

    final.hex = DEC(final.r, final.g, final.b);
    printf("HEX: %u\n", final.hex);
    return (final);
}

t_vec v_scale(float scale, t_vec *vec)
{
    t_vec new;

    new.x = vec->x *scale;
    new.y = vec->y *scale;
    new.z = vec->z *scale;

    return (new);
}

float v_mag(t_vec *v1, t_vec *v2)
{
    float x = (v2->x - v1->x) * (v2->x - v1->x);
    float y = (v2->y - v1->y) * (v2->y - v1->y);
    float z = (v2->z - v1->z) * (v2->z - v1->z);
    float magnitude = sqrtf(x + y + z);
    return (magnitude);
}

t_vec cross_p(t_vec a, t_vec b)
{
    t_vec cross;

    cross.x = a.x * b.z - a.z * b.y;
    cross.y = a.z * b.x - a.x * b.z;
    cross.z = a.x * b.y - a.y * b.x;

    return (cross);
}

t_vec v_sub(t_vec *v1, t_vec *v2)
{
    t_vec new;

    new.x = v1->x - v2->x;
    new.y = v1->y - v2->y;
    new.z = v1->z - v2->z;
    return (new);
}

t_vec v_from_2p(t_vec start, t_vec end)
{
    t_vec vector;
    vector = v_sub(&end, &start);
    vector.x = sqrtf(vector.x * vector.x);
    vector.y = sqrtf(vector.y * vector.y);
    vector.z = sqrtf(vector.z * vector.z);
    return (vector);
}

t_vec v_add(t_vec *v1, t_vec *v2)
{
    t_vec new;
    // exit(0);
    new.x = v1->x + v2->x;
    new.y = v1->y + v2->y;
    new.z = v1->z + v2->z;

    return (new);
}

t_vec v_mult(t_vec *v1, t_vec *v2)
{
    t_vec new;

    new.x = v1->x * v2->x;
    new.y = v1->y * v2->y;
    new.z = v1->z * v2->z;

    return (new);
}

float dot_p(t_vec *v1, t_vec *v2)
{
    float dot;
    float a;
    float b;
    float c;

    a = v1->x * v2->x;
    b = v1->y * v2->y;
    c = v1->z * v2->z;
    /*
        printf("**********DOT**********\n");
        printf("v1x:%f\n", v1->x);
        printf("v1y:%f\n", v1->y);
        printf("v1z:%f\n", v1->z);

        printf("a:%f\n", a);
        printf("b:%f\n", b);
        printf("c:%f\n", c); */

    dot = a + b + c;
    // printf("dot:%f\n", dot);
    return (dot);
}

static double sqr(double n)
{
    return (n * n);
}

double length_squared(t_vec v)
{
    return (sqr(v.x) + sqr(v.y) + sqr(v.z));
}

double length(t_vec v)
{
    return (sqrt(length_squared(v)));
}

double angle_bet_vs(t_vec *v1, t_vec *v2)
{
    float scalar = dot_p(v1, v2);
    float mag1 = length(*v1);
    float mag2 = length(*v2);
    float angle = scalar / (mag1 * mag2);
    // printf("angle should be between 0 & 180: %f\n", acos(angle));
    return (acos(angle));
}
