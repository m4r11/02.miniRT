/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:02:31 by mvaldeta          #+#    #+#             */
/*   Updated: 2022/04/19 18:36:34 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

int limit_kernel(t_frame *rt, float source, float deviation, char xy)
{
  int limit;

  if (xy == 'x')
    limit = rt->window_w - 1;
  if (xy == 'y')
    limit = rt->window_h - 1;
  if (deviation > limit)
    return (limit);
  if (deviation < 0)
    return (source);
  return (deviation);
}

t_boxblur gaussian_var(int x, int y)
{
  t_boxblur blur;
  int n_x[] = {-1, 0, 1};
  int n_y[] = {-1, 0, 1};

  /* first col */
  // printf("REF-> ox:%d & oy:%d \n", x, y);
  blur.m_00.x = x + n_x[0];
  blur.m_00.y = y + n_y[0];
  // printf("00-> x:%d & y:%d \n", blur.m_00.x, blur.m_00.y);

  blur.m_01.x = x + n_x[0];
  blur.m_01.y = y + n_y[1];
  // printf("01-> x:%d & y:%d \n", blur.m_01.x, blur.m_01.y);

  blur.m_02.x = x + n_x[0];
  blur.m_02.y = y + n_x[2];
  // printf("02-> x:%d & y:%d \n", blur.m_02.x, blur.m_02.y);

  /* second col */
  blur.m_10.x = x + n_x[1];
  blur.m_10.y = y + n_y[0];
  // printf("10-> x:%d & y:%d \n", blur.m_10.x, blur.m_10.y);

  blur.m_11.y = y + n_y[1];
  blur.m_11.x = x + n_x[1];
  // printf("10-> x:%d & y:%d \n", blur.m_11.x, blur.m_11.y);

  blur.m_12.x = x + n_x[1];
  blur.m_12.y = y + n_x[2];
  // printf("10-> x:%d & y:%d \n", blur.m_12.x, blur.m_12.y);
  /* third col */
  blur.m_20.x = x + n_x[2];
  blur.m_20.y = y + n_y[0];
  // printf("20-> x:%d & y:%d \n", blur.m_20.x, blur.m_20.y);

  blur.m_21.x = x + n_x[2];
  blur.m_21.y = y + n_y[1];
  // printf("21-> x:%d & y:%d \n", blur.m_21.x, blur.m_21.y);

  blur.m_22.x = x + n_x[2];
  blur.m_22.y = y + n_x[2];
  // printf("22-> x:%d & y:%d \n", blur.m_22.x, blur.m_22.y);
  // exit(0);
  return (blur);
}

void depth_map(t_frame *rt, int x, int y, unsigned int pixel_color)
{
/*   rt->pixel_map.map[x + 1][y] = pixel_color;
  rt->pixel_map.map[x - 1][y] = pixel_color; */
  rt->pixel_map.map[x][y] = pixel_color;
/*   rt->pixel_map.map[x][y - 1] = pixel_color;
  rt->pixel_map.map[x][y + 1] = pixel_color; */
}

unsigned int apply_blur(t_frame *rt, int x, int y)
{
  unsigned int sum;
  int r = 0;
  int g = 0;
  int b = 0;
  int n = 0;

  int i;
  int j;
  int k;
  int radius;
  k = rt->out_of_focus;
  radius = k;
  if (x < radius || y < radius)
    return (0);
  i = y - radius;
  j = x - radius;

  t_color gb_1;
  t_color gb_2;
  t_color gb_3;
  t_color gb_4;
  t_color gb_5;
  t_color gb_6;
  t_color gb_7;
  t_color gb_8;
  t_color gb_9;

  while (i < y + radius)
  {
    j = x - radius;
    while (j < x + radius)
    {
        gb_1 = c_color_components(rt->pixel_map.map[j - 1][i - 1]);
        gb_2 = c_color_components(rt->pixel_map.map[j - 1][i]);
        gb_3 = c_color_components(rt->pixel_map.map[j - 1][i + 1]);
        gb_4 = c_color_components(rt->pixel_map.map[j][i - 1]);
        gb_5 = c_color_components(rt->pixel_map.map[j][i]);
        gb_6 = c_color_components(rt->pixel_map.map[j][i + 1]);
        gb_7 = c_color_components(rt->pixel_map.map[j + 1][i - 1]);
        gb_8 = c_color_components(rt->pixel_map.map[j + 1][i]);
        gb_9 = c_color_components(rt->pixel_map.map[j + 1][i + 1]);
        r += ((gb_1.r + gb_2.r + gb_3.r + gb_4.r + gb_5.r + gb_6.r + gb_7.r + gb_8.r + gb_9.r) * 2);
        g += ((gb_1.g + gb_2.g + gb_3.g + gb_4.g + gb_5.g + gb_6.g + gb_7.g + gb_8.g + gb_9.g) * 2);
        b += ((gb_1.b + gb_2.b + gb_3.b + gb_4.b + gb_5.b + gb_6.b + gb_7.b + gb_8.b + gb_9.b) * 2);
  
        n += radius;
        j += 1;
    }
    i += 1;
  }

  r = sqrt((r) / n);
  g = sqrt((g) / n);
  b = sqrt((b) / n);
  // printf("r:%d, g:%d, b:%d, n:%d\n", r, g, b, n);
  // sum = DEC(r, g, b);
  // exit(0);
  sum = DEC(c_range(r, 0, 255), c_range(g, 0, 255), c_range(b, 0, 255));
  //depth_map(rt, x, y, sum);
  return (sum);
}