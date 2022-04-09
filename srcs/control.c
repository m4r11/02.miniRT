/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 14:28:56 by user              #+#    #+#             */
/*   Updated: 2022/04/09 03:28:12 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"
#define KRED "\x1B[31m"

int key_zoom(int keycode, t_frame *rt)
{
    if (keycode == 6)
    {
        printf("keycode Z: %d\n", keycode);
        print_vector(*rt->scene->c->cam_coord, "cam_test_control");
        rt->scene->c->cam_coord->z += 1;
        print_vector(*rt->scene->c->cam_coord, "cam_test_control");
    }
    else
        printf("keycode TEST: %d\n", keycode);
    return (keycode);
}

int key_kill(int keycode, t_frame *rt)
{
    printf("keycode: %d\n", keycode);
    if (keycode == 1216)
    {
        printf("\tRED DOT\n");
        mlx_destroy_window(rt->mlx_ptr, rt->win_ptr);
        printf("x_x Killing Mini x_x \n");
        printf("* Window killed!\n");
        printf("* Scene killed!\n");
        printf("* List killed!\n");
        printf("* Frame killed!\n");
        exit(0);
    }
    if (keycode == 53)
    {
        mlx_destroy_window(rt->mlx_ptr, rt->win_ptr);
        printf("\tHURRAY YOU PRESSED ESCAPE\n");
        kill_frame(rt);
        printf("x_x Killing Mini x_x \n");
        printf("* Window killed!\n");
        printf("* Scene killed!\n");
        printf("* List killed!\n");
        printf("* Frame killed!\n");
        exit(0);
    }
    if (keycode == 34)
    {
        printf("keycode IN: %d\n", keycode);
        print_vector(*rt->scene->c->cam_coord, "cam_test_control");
        rt->scene->c->cam_coord->x += 5;
        rt->scene->c->cam_coord->y += 5;
        rt->scene->c->cam_coord->z += 5;
        mlx_destroy_image(rt->mlx_ptr, rt->obj_img.img_ptr);
        rt->obj_img.img_ptr = mlx_new_image(rt->mlx_ptr, rt->window_w, rt->window_h);
        rt->obj_img.data = (int *)mlx_get_data_addr(rt->obj_img.img_ptr, &rt->obj_img.bits_per_pixel, &rt->obj_img.line_length, &rt->obj_img.endian);
        // mlx_clear_window(rt->mlx_ptr, rt->win_ptr);

        render(rt);
        // print_vector(*rt->scene->c->cam_coord, "cam_test_control");
    }
    if (keycode == 31)
    {
        printf("keycode OUT: %d\n", keycode);
        print_vector(*rt->scene->c->cam_coord, "cam_test_control");
        //print_vector(*rt->scene->c->cam_coord, "cam_test_control");
        rt->scene->c->cam_coord->x -= 5;
        rt->scene->c->cam_coord->y -= 5;
        rt->scene->c->cam_coord->z -= 5;
        mlx_destroy_image(rt->mlx_ptr, rt->obj_img.img_ptr);
        rt->obj_img.img_ptr = mlx_new_image(rt->mlx_ptr, rt->window_w, rt->window_h);
        rt->obj_img.data = (int *)mlx_get_data_addr(rt->obj_img.img_ptr, &rt->obj_img.bits_per_pixel, &rt->obj_img.line_length, &rt->obj_img.endian);
        // mlx_clear_window(rt->mlx_ptr, rt->win_ptr);

        render(rt);
        // print_vector(*rt->scene->c->cam_coord, "cam_test_control");
    }
    if (keycode == 40)
    {
        printf("keycode LL: %d\n", keycode);
        print_vector(*rt->scene->l->light_coord, "ltest_control");
        rt->scene->l->light_coord->x -= 10;
        mlx_destroy_image(rt->mlx_ptr, rt->obj_img.img_ptr);
        rt->obj_img.img_ptr = mlx_new_image(rt->mlx_ptr, rt->window_w, rt->window_h);
        rt->obj_img.data = (int *)mlx_get_data_addr(rt->obj_img.img_ptr, &rt->obj_img.bits_per_pixel, &rt->obj_img.line_length, &rt->obj_img.endian);
        // mlx_clear_window(rt->mlx_ptr, rt->win_ptr);

        render(rt);
    }
    if (keycode == 37)
    {
        printf("keycode LR: %d\n", keycode);
        print_vector(*rt->scene->l->light_coord, "ltest_control");
        rt->scene->l->light_coord->x += 10;
        mlx_destroy_image(rt->mlx_ptr, rt->obj_img.img_ptr);
        rt->obj_img.img_ptr = mlx_new_image(rt->mlx_ptr, rt->window_w, rt->window_h);
        rt->obj_img.data = (int *)mlx_get_data_addr(rt->obj_img.img_ptr, &rt->obj_img.bits_per_pixel, &rt->obj_img.line_length, &rt->obj_img.endian);
        // mlx_clear_window(rt->mlx_ptr, rt->win_ptr);

        render(rt);
    }
    if (keycode == 126)
    {
        printf("keycode arrow UP: %d\n", keycode);
        t_obj *search_plane;
        search_plane = rt->objs_first;
        while (search_plane->id1 != 'p')
            search_plane = search_plane->next;
        // search_plane->obj_coord->x += 100;
        // search_plane->obj_coord->x += 10;
        //search_plane->obj_coord->z -= 10;
        //search_plane->obj_coord->x += 10;
        search_plane->obj_norm->z += 10;
        // search_plane->obj_coord->z -= 10;
        // search_plane->obj_coord->z -= 100;
        // search_plane->obj_norm->y -= 10;
        // search_plane->obj_norm->z -= 10;
        print_vector(*search_plane->obj_norm, "P:plane_test_coordcontrol");
        print_vector(*search_plane->obj_coord, "plane_test_coordcontrol");
        mlx_destroy_image(rt->mlx_ptr, rt->obj_img.img_ptr);
        rt->obj_img.img_ptr = mlx_new_image(rt->mlx_ptr, rt->window_w, rt->window_h);
        rt->obj_img.data = (int *)mlx_get_data_addr(rt->obj_img.img_ptr, &rt->obj_img.bits_per_pixel, &rt->obj_img.line_length, &rt->obj_img.endian);
        // mlx_clear_window(rt->mlx_ptr, rt->win_ptr);

        render(rt);
    }
    if (keycode == 125)
    {
        printf("keycode arrow DOWN: %d\n", keycode);
        t_obj *search_plane;
        search_plane = rt->objs_first;
        while (search_plane->id1 != 'p')
            search_plane = search_plane->next;
        // search_plane->obj_coord->x -= 100;
        // search_plane->obj_coord->x -= 10;
        //search_plane->obj_coord->z += 10;
        //search_plane->obj_coord->x -= 10;
        search_plane->obj_norm->z -= 10;
        // search_plane->obj_coord->z += 10;
        // search_plane->obj_coord->z += 10;
        // search_plane->obj_coord->z += 100;
        // search_plane->obj_norm->y += 10;
        // search_plane->obj_norm->z += 10;
        // search_plane->obj_norm->z += 10;
        print_vector(*search_plane->obj_norm, "P:plane_test_coordcontrol");
        print_vector(*search_plane->obj_coord, "plane_test_coordcontrol");
        mlx_destroy_image(rt->mlx_ptr, rt->obj_img.img_ptr);
        rt->obj_img.img_ptr = mlx_new_image(rt->mlx_ptr, rt->window_w, rt->window_h);
        rt->obj_img.data = (int *)mlx_get_data_addr(rt->obj_img.img_ptr, &rt->obj_img.bits_per_pixel, &rt->obj_img.line_length, &rt->obj_img.endian);

        render(rt);
    }
        return (keycode);
}

    /* down _
    keycode TEST: 125

    esc
    keycode TEST: 53

    keycode: 1216
    cross x

    left <-
    keycode TEST: 123

    top ^
    keycode TEST: 126

    right ->
    keycode TEST: 124

    zoom in i
    keycode: 34

    zoom out o
    keycode: 31
    */
