/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:05:27 by mvaldeta          #+#    #+#             */
/*   Updated: 2021/12/03 09:49:11 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

void create_image(t_frame *rt, int which)
{
  if(which == BKG)
  {
    rt->bkg_img.img_ptr = mlx_new_image(rt->mlx_ptr, rt->window_w, rt->window_h);
    rt->bkg_img.data = (int *)mlx_get_data_addr(rt->bkg_img.img_ptr, &rt->bkg_img.bits_per_pixel, &rt->bkg_img.line_length, &rt->bkg_img.endian);
    return;
  }
  if(which == OBJ)
  {
    rt->obj_img.img_ptr = mlx_new_image(rt->mlx_ptr, rt->window_w, rt->window_h);
    rt->obj_img.data = (int *)mlx_get_data_addr(rt->obj_img.img_ptr, &rt->obj_img.bits_per_pixel, &rt->obj_img.line_length, &rt->obj_img.endian);
    return;
  }
}

/* void add_img_queue(t_frame *rt)
{
  
} */