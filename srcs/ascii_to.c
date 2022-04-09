/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_to.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:59:20 by user              #+#    #+#             */
/*   Updated: 2022/03/14 16:02:18 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

/* int filetype_is_valid(char *arg, char *file_type)
{
    int file;
    file = ft_strlen(arg);
    if(arg[file - 1] == file_type[2] && arg[file - 2] == file_type[1] &&  arg[file - 3] == file_type[0])
        return(1);
    else
        return(0);
} */

int ascii_to_int(char *data)
{
    int i;
    int sign = 1;
    int nbr = 0;

    i = 0;
    if (data[0] == '-')
    {
        sign = -1;
        i += 1;
    }
    if(data[0] == '0')
        return(0);
    while (data[i])
    {
        nbr = data[i] - 48 + nbr;
        i++;
        if(data[i])
            nbr *= 10;
    }
    return (nbr *= sign);
}

float ascii_to_float(char *data)
{
    float point;
    int power;
    int i = 0;
    int sign = 1;
    power = 1.0;    
    point = 0.0;

    if(data[i] == '-')
    {
        sign *= -1;
        i += 1;
    }
    while(data[i] && data[i] != '\n' && data[i] != '.')
    {
        point = 10 * point + (data[i] - '0');
        i++;
    }

    if(data[i] == '.')
    {
        i++;
        while(data[i])
        {
            point = 0.01 * point + (data[i] - '0');
            power *= 0.01;
            i++;
        }
    }
    return((point * sign) / power);
}

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


unsigned int ascii_to_hex(int r, int g, int b)
{
    uint32_t hex;
  
    hex = ((r & 0xff) << 16) + ((g & 0xff) << 8) + ((b & 0xff));
    return (hex);
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