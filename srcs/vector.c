/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldeta <mvaldeta@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:50:22 by user              #+#    #+#             */
/*   Updated: 2021/12/09 18:13:07 by mvaldeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

t_vec normalize(t_vec *p)
{
    float w = sqrt(p->x * p->x + p->y * p->y + p->z * p->z);
    p->x /= w;
    p->y /= w;
    p->z /= w;
    return (*p);
}

t_color c_mix(float hit, float light, t_color *obj_color)
{
    t_color model;
    t_color ilumination;

    model = c_blend(hit, obj_color);
    ilumination = c_luminance(light, &model);

    printf("->model %u\n", model.hex);
    printf("->luminance %u\n", ilumination.hex);

    return(ilumination);
}

t_color c_blend(float alpha, t_color *color)
{
    t_color new;
    float ratio;
    ratio = alpha;
   // alpha = BLACK(alpha);
    printf("ALPHA in blend : %f\n", alpha);
    alpha = BLACK(alpha);
    printf("ALPHA after max : %f\n", alpha);
    new.r = (alpha) * BIT(color->r);
    new.g = (alpha) * BIT(color->g);
    new.b = (alpha) * BIT(color->b);

    new.hex = DEC(new.r, new.g, new.b);
    printf("NEW X : %u\n", new.hex);
    color = &new;
    return (new);
}

t_color c_luminance(float alpha, t_color *color)
{
    t_color new;
    float ratio;
    ratio = alpha;
   // alpha = BLACK(alpha);
    printf("\nALPHA in lum : %f\n", alpha);
    alpha = LIGHT(alpha);
    printf("\nALPHA after lum after p : %f\n", alpha);
    new.r = (alpha) * BIT(color->r);
    new.g = (alpha) * BIT(color->g);
    new.b = (alpha) * BIT(color->b);

    new.hex = DEC(new.r, new.g, new.b);
    printf("NEW X : %u\n", new.hex);
    color = &new;
    return (new);
}

t_vec v_scale(float scale, t_vec *vec)
{
    t_vec new;

    new.x = vec->x *scale;
    new.y = vec->y *scale;
    new.z = vec->z *scale;

    return (new);
}

t_vec v_sub(t_vec *v1, t_vec *v2)
{
    t_vec new;

    new.x = v1->x - v2->x;
    new.y = v1->y - v2->y;
    new.z = v1->z - v2->z;

    /*     printf("**********SUBTRACTION********\n");
        printf("v1x:%f\n", v1->x);
        printf("v1y:%f\n", v1->y);
        printf("v1z:%f\n", v1->z);
        printf("v2z:%f\n", v2->z);

        printf("new_x:%f\n", new.x);
        printf("new_y:%f\n", new.y);
        printf("new_z:%f\n", new.z); */
    return (new);
}

t_vec v_add(t_vec *v1, t_vec *v2)
{
    t_vec new;
    //exit(0);
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