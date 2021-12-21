/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:53:53 by mvaldeta          #+#    #+#             */
/*   Updated: 2021/12/21 02:49:15 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

void	map_to_img(t_data data, int x, int y, int color)
{
	data.data[(y * data.line_length + x * (data.bits_per_pixel / 8) / 4)] = color;
}

void window_init(t_frame *rt)
{
	rt->mlx_ptr = mlx_init();
	rt->win_ptr = mlx_new_window(rt->mlx_ptr, rt->window_w, rt->window_h, "A cool rt");
	rt->obj_img.img_ptr = mlx_new_image(rt->mlx_ptr, rt->window_w, rt->window_h);
    rt->obj_img.data = (int *)mlx_get_data_addr(rt->obj_img.img_ptr, &rt->obj_img.bits_per_pixel, &rt->obj_img.line_length, &rt->obj_img.endian);
}

void background_to_window(t_frame *rt)
{
    mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->bkg_img.img_ptr, 0, 0);
}

void obj_to_window(t_frame *rt)
{
    mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->obj_img.img_ptr, 0, 0);
}

void my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
    size_t offset;

    offset = ((y * 4000 + x * data->bits_per_pixel / 8) / 4);
    data->data[offset] = 0;
    data->data[offset] = color;
}