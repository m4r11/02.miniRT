/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:45:46 by user              #+#    #+#             */
/*   Updated: 2022/03/27 19:02:39 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtlib.h"

/* useful equation cheat sheet:
Standard line eq:
𝑎 𝑥 + 𝑏 𝑦 + 𝑐 = 0
The equation of the line can also be realized as a dot product of two vectors as
Standard eq plane :
 𝑎 𝑥 + 𝑏 𝑦 + 𝑐 𝑧 + 𝑑 = 0
Plane from 2 points:
𝑎 ( 𝑥 − 𝑥 ) + 𝑏 ( 𝑦 − 𝑦 ) + 𝑐 ( 𝑧 − 𝑧 ) = 0
Normal vector on olane given two vects on point:
cross_p

ray_plane intersections:
point in plane: (p−p0)⋅n=0
ray : l0+l∗t=p
two eqs in one : (l0+l∗t−p0)⋅n=0
compute t:
t = =−(l0−p0)⋅n/ l⋅n
- l0 is the origin of the ray
-  l is the ray direction
- p0 point far away in plane
- n normm vec
*/

float ray_sphere(t_ray *r, t_obj *s, t_vec obj_coord)
{

	t_vec d = v_add(r->start, r->dir);
	t_vec dist = v_sub(&obj_coord, &d);

	float radius = (s->diameter) / 2;
	float a = dot_p(r->dir, r->dir);
	float b = 2.0 * dot_p(r->dir, &dist);
	float c = dot_p(&dist, &dist) - (radius * radius);
	float discr = b * b - 4 * a * c;
	if (discr >= 0)
	{
		if (discr == 0)
		{
			float t0 = -0.5 * b / a;
			return (t0);
		}
		// float q = MAX(-0.5 * (b + sqrtf(discr)), -0.5 * (b - sqrtf(discr)));
		float t1 = (-b - sqrtf(discr)) / (2 * a);
		float t2 = (-b + sqrtf(discr)) / (2 * a);
		if (t1 > t2)
		{
			float tmp = t1;
			t1 = t2;
			t2 = tmp;
		}
		if (t1 < 0)
			t1 = t2;
		if (t1 > 0)
		{
			//printf("\tt1: %f\n", t1);
			return (t1);
		}
	}
	return (NO_HIT);
}

float ray_cy(t_ray *r, t_obj *s, t_vec obj_coord)
{
	t_vec dir = *r->dir;
	t_vec pos = *r->start;
	t_vec center = obj_coord;
	float height = s->height;
	float radius = s->diameter / 2;
	// double rot = (M_PI * 45) / 180

	t_vec bot = v_3(center.x, center.y - (height / 2), center.z);
	t_vec top = v_3(center.x, center.y + (height / 2), center.z);
	// t_vec top = v_3(obj_coord.x, obj_coord.y + (height / 2), obj_coord.z);
	float a = (dir.x * dir.x) + (dir.z * dir.z);
	float b = 2 * (dir.x * (pos.x - bot.x)) + (2 * dir.z) * (pos.z - bot.z);
	float c = (pos.x - bot.x) * (pos.x - bot.x) + (pos.z - bot.z) * (pos.z - bot.z) - (radius * radius);

	float delta = b * b - 4 * (a * c);
	if (fabs(delta) < 0.001)
		return (NO_HIT);
	if (delta < 0.0)
		return (NO_HIT);

	float t1 = (-b - sqrt(delta)) / (2 * a);
	float t2 = (-b + sqrt(delta)) / (2 * a);
	float t;

	if (t1 > t2)
		t = t2;
	else
		t = t1;

	float rd = pos.y + (t * dir.y);
	t_vec p = v_scale(t, r->dir);
	p = v_add(r->start, &p);
	float cap = (p.x * p.x) + (p.z * p.z);
	// print_vector(p, "lol");
	cap = sqrtf(cap);
	/* 	printf("cap%f\n", cap);
		printf("radius%f\n", radius);
		exit(0); */
	if (fabs(cap) <= radius)
	{
		// printf("inside%f\n", t);
		return (t);
	}
	// exit(0);
	if ((rd >= bot.y) && (rd <= top.y))
	{
		return (t);
	}
	else
		return (NO_HIT);
}

float ray_plane(t_ray *r, t_obj *p)
{

	float t;
	float o;
	float pp;
	float v;
	float d;
	p->test = v_add(r->start, r->dir);
	pp = solve_q(p, *p->obj_coord);
	o = solve_q(p, *r->start);
	v = solve_q(p, *r->dir);
	d = solve_d(p, p->test);
	t = (d / v);
	if (v > 1e-9)
	{
		if(t < 0)
			t *= -1.0;
		return(t);
	}
	return (NO_HIT);
}
