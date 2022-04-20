/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:20:09 by mvaldeta          #+#    #+#             */
/*   Updated: 2022/03/10 19:58:21 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

int minirt(void)
{
    t_frame *rt;
    t_parse *info;
    rt = init_frame();
    info = init_parse();

    fill_frame(info, rt);
    write(1, "\tframe\n", 7);

    create_scene(info, rt);
    write(1, "\tscene\n", 7);

    window_init(rt);
    write(1, "\twindow\n", 8);

    create_objs(rt);
    write(1, "\tobjects\n", 9);
    //exit(0);

    render(rt);
    write(1, "\trender out\n", 11);
    mlx_loop(rt->mlx_ptr);
    return(0);
}

int main(int ac, char **av)
{
    if (ac == 2)
    {
        if (filetype_is_valid(av[1], ".rt"))
            minirt();
        return(1);
    }
    else
        write(1, "Error\n", 6);
    return (0);
}