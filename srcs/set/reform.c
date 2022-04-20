/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reform.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:59:20 by user              #+#    #+#             */
/*   Updated: 2022/04/20 13:25:14 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

t_vec *ascii_to_vec(char *data)
{
    t_vec *vec = NULL;

    vec = malloc(sizeof(t_vec));
    char **vectorial;

    vectorial = ft_split(data, ',');
    
    vec->x = ascii_to_float(vectorial[0]);
    vec->y = ascii_to_float(vectorial[1]);
    vec->z = ascii_to_float(vectorial[2]);
    return (vec);
}


t_color *ascii_to_rgb(char *data)
{
    char **colors;
    t_color *color = NULL; 
    color = malloc(sizeof(t_color));
       
    colors = ft_split(data, ',');

    color->r = ascii_to_int(colors[0]);
    color->g = ascii_to_int(colors[1]);
    color->b = ascii_to_int(colors[2]);
    color->hex = DEC(color->r, color->g, color->b);
    return (color);
}