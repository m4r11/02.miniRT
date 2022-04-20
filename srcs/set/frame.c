/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:35:32 by mvaldeta          #+#    #+#             */
/*   Updated: 2022/02/04 15:45:15 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

t_frame *fill_frame(t_parse *raw, t_frame *rt)
{
    char *data;
    char id1;
    char id2;
   
    while ((data = get_next_line(0)))
    {
        if(data == NULL)
            break;
        id1 = data[0];
        id2 = data[1];
        if (id1 == 'A')
            raw->ambient = save_raw(data);
        if (id1 == 'C')
            raw->camera = save_raw(data);
        if (id1 == 'L')
            raw->light = save_raw(data);
        if (id1 == 's' && id2 == 'p')
            add_new_obj(rt, data);
        if (id1 == 'p' && id2 == 'l')
            add_new_obj(rt, data);
        if (id1 == 'c' && id2 == 'y')
            add_new_obj(rt, data);
        free(data);
    }
    return (rt);
}

t_frame *kill_frame(t_frame *rt)
{
    free(rt);
    rt = NULL;
    return (rt);
}