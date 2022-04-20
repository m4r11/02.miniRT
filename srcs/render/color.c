/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldeta <mvaldeta@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:19:06 by user              #+#    #+#             */
/*   Updated: 2022/03/04 17:28:53 by mvaldeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

/* declaring black */
const t_color black = {0, 0, 0, 0};
const t_color yellow = {0, 0, 255, 0};
/* declaring primaries */
const t_color red = {1, 0, 0, 0};
const t_color green = {0, 1, 0, 0};
const t_color blue = {0, 0, 1, 0};
const int rgb[3] = {1, 2, 3};

/* 
B = LONG \ 65536
G = (LONG - B * 65536) \ 256
R = LONG - B * 65536 - G * 256 
const r = (number & 0xff0000) >> 16;
 const g = (number & 0x00ff00) >> 8;
 const b = (number & 0x0000ff);*/


t_color c_color_components(unsigned int decimal_color)
{
    t_color new;
    new.r = (decimal_color & 0xff0000) >> 16;
    new.g = (decimal_color & 0x00ff00) >> 8;
    new.b = (decimal_color & 0x0000ff);
    new.r *= new.r;
    new.g *= new.g;
    new.b *= new.b;
/*     new.r = (int)sqrt(new.r);
    new.g = (int)sqrt(new.g);
    new.b = (int)sqrt(new.b); */

    return(new);
}

t_color c_mix_2colors(t_color one, t_color two)
{
    t_color mixed;

    mixed.r = c_range(one.r + two.r, 0, 255);
    mixed.g = c_range(one.g + two.g, 0, 255);
    mixed.b = c_range(one.b + two.b, 0, 255);
    return(mixed);
}

t_color c_mix_hue(t_color one, t_color two, t_color hue)
{
    t_color mixed;
    mixed = c_mix_2colors(one, two);
    mixed = c_mix_2colors(hue, mixed);
    return(mixed);
}

t_color c_new_color(int r, int g, int b)
{
    t_color new;
    new.r = r;
    new.g = g;
    new.b = b;
    new.hex = DEC(r, g, b);
    return(new);
}

int c_increase(int max)
{
    if (max > L)
        return (max - L);
    return (0);
}

float c_percentage(int color)
{
    return (color / 255);
}

t_color c_isolate_hue(t_color *check)
{
    float c[3];
    int index = 0;
    int highest = 0;
    int hue[3] = {0};
    t_color hued;

    c[0] = c_percentage(check->r);
    c[1] = c_percentage(check->g);
    c[2] = c_percentage(check->b);

    highest = c[0];
    while (c[index])
    {
        if (highest < c[index])
        {
            hue[index - 1] = 0;
            highest = c[index];
            hue[index] = 1;
        }
        index++;
    }
    hued = c_new_color(hue[0] * check->r, hue[1] * check->g, hue[2] * check->b);
    return (hued);
}

t_color c_mix(t_frame *rt, t_color *obj, double spec, double difuse)
{
    t_color mixed;
    t_color source;
    t_color ambient;
    //t_color hued;

    source = *rt->scene->l->light_color;
    
    ambient = *rt->scene->a->amb_color;
    //ambient = c_mix_2colors(*rt->scene->a->amb_color, *rt->scene->l->light_color);
    //*source = yellow;
    mixed.r = c_range((source.r * spec) + (ambient.r * (difuse)) + (obj->r * difuse), 0, 255);
    mixed.g = c_range((source.g * spec) + (ambient.g * (difuse)) + (obj->g * difuse), 0, 255);
    mixed.b = c_range((source.b * spec) + (ambient.b * (difuse)) + (obj->b * difuse), 0, 255);
/*     mixed.r = c_range((source.r * spec) + (ambient.r * (difuse / 2)) + (source.r * (difuse / 2)) + (obj->r * difuse), 0, 255);
    mixed.g = c_range((source.g * spec) + (ambient.g * (difuse / 2)) + (source.g * (difuse / 2)) + (obj->g * difuse), 0, 255);
    mixed.b = c_range((source.b * spec) + (ambient.b * (difuse / 2)) + (source.b * (difuse / 2)) + (obj->b * difuse), 0, 255); */
    mixed.hex = DEC(mixed.r, mixed.g, mixed.b);
    return (mixed);
}

t_color c_grade(t_frame *rt, t_color *color, double spec, double difuse)
{
    t_color new;
    new = c_mix(rt, color, spec, difuse);
    new.hex = DEC(new.r, new.g, new.b);
    return (new);
}