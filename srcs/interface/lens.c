/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lens.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 13:45:34 by user              #+#    #+#             */
/*   Updated: 2022/04/20 23:51:50 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

float gaussian_blur();


/* 
DOF = /2f (M + 1) / M) / ((fM / Nc) - (Nc / fM))

N the nominal aperture
M the magnification
f is the focal length
c the circle of confusion
	
for DX digital format d =	0.020
for FX digital format d =	0.025
for 35mm film format  d =	0.025
for 6x6cm film format d =	0.045
for 4x5in film format d =	0.1



~ 35mm Full Format Focal Len by FOV rapid table
? | FOV | DOF   | CIRCLEC D-A | LENS | GROUP      | VISUAL
* | 2   | 50    | 0.36 - 0.03 | 1131 | SUPER TELE | SCALE++ FAR FOCUS
* | 20  | 60    |             | 102  | TELE       | SCALE+ FAR FOCUS
* | 30  | 5     |             | 67   | MEDIUM TELE| MEDIUM SCALE 
* | 50  | 5     |             | 38   | standard   |
* | 60  | 5     |             | 31   | WIDE ANGLE |
* | 80  | 5     |       4     | 21   | SUPER WIDE |
* | 100 | 5     |             | 15   | SUPER WIDE |
*/

float get_focal_len(float fov)
{
    float fl;
    float half = fov / 2;
    fl = (36 * 0.5) / (tan(half / 52.296));
    return((fl));
}

float get_hyperfocal_dist(float fl, float ap, float c)
{
    return((fl / ap * c));
}

float get_near_dof(float fl)
{
    return(fl - (0.6 * (fl)));
}

float get_far_dof(float fl)
{
    return(fl + (0.3 * (fl)));
}

float get_dof_range(float near, float far)
{
    return(far - near);
}






/* void  out_of_focus(t_ray *prime)
{
    prime->dir = sin;
} */