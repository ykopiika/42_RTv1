/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 16:01:12 by ykopiika          #+#    #+#             */
/*   Updated: 2019/10/14 18:43:01 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	value_clamp(t_parse *p)
{
	if (p->fgrs != NULL)
	{
		min_max_vect(&p->fgrs->color, 0.0, 255.0);
		min_max_int(&p->fgrs->specul, 0, 3000);
		min_max_double(&p->fgrs->radius, 0.1, 100000.0);
		min_max_double(&p->fgrs->angl, 1.0, 179.0);
		if (!p->fgrs->dir.x && !p->fgrs->dir.y && !p->fgrs->dir.z)
			p->fgrs->dir.y = 1;
	}
}

void	camera_rotate(t_vct *dir_ray, const t_vct *restrict rot)
{
	*dir_ray = (t_vct){.x = dir_ray->x * cos(rot->x)
								+ dir_ray->z * sin(rot->x),
							.y = dir_ray->y,
							.z = -dir_ray->x * sin(rot->x)
								+ dir_ray->z * cos(rot->x)};
	*dir_ray = (t_vct){.x = dir_ray->x,
						.y = dir_ray->y * cos(rot->y)
							+ dir_ray->z * sin(rot->y),
						.z = -dir_ray->y * sin(rot->y)
							+ dir_ray->z * cos(rot->y)};
	*dir_ray = (t_vct){.x = dir_ray->x * cos(rot->z)
								- dir_ray->y * sin(rot->z),
						.y = dir_ray->x * sin(rot->z)
							+ dir_ray->y * cos(rot->z),
						.z = dir_ray->z};
}

void	min_max_vect(t_vct *v, double min, double max)
{
	if (v->x < min)
		v->x = min;
	if (v->x > max)
		v->x = max;
	if (v->y < min)
		v->y = min;
	if (v->y > max)
		v->y = max;
	if (v->z < min)
		v->z = min;
	if (v->z > max)
		v->z = max;
}

void	min_max_double(double *dst, double min, double max)
{
	if (*dst < min)
		*dst = min;
	if (*dst > max)
		*dst = max;
}

void	min_max_int(int *dst, int min, int max)
{
	if (*dst < min)
		*dst = min;
	if (*dst > max)
		*dst = max;
}
