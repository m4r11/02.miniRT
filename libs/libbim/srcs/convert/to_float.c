/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:10:04 by user              #+#    #+#             */
/*   Updated: 2022/04/20 13:10:30 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bimlib.h"

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