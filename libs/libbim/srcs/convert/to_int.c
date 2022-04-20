/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:06:49 by user              #+#    #+#             */
/*   Updated: 2022/04/20 13:08:24 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bimlib.h"

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
