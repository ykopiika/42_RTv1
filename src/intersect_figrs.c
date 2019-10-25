/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_figrs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 19:52:33 by ykopiika          #+#    #+#             */
/*   Updated: 2019/10/14 16:46:37 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_td	calculate_discriminant(double coeff1, double coeff2, double coeff3)
{
	double	pnt1;
	double	pnt2;
	double	dscrmnnt;

	dscrmnnt = coeff2 * coeff2 - 4 * coeff1 * coeff3;
	if (dscrmnnt < 0)
		return ((t_td){INF, INF});
	pnt1 = (-coeff2 + sqrt(dscrmnnt)) / (2.0 * coeff1);
	pnt2 = (-coeff2 - sqrt(dscrmnnt)) / (2.0 * coeff1);
	return ((t_td){pnt1, pnt2});
}

t_td	sphere_intersection(t_vct *origin, t_vct *ray_dir, t_fgrs *sphere)
{
	t_vct	origin_center;
	double	coeff1;
	double	coeff2;
	double	coeff3;

	origin_center = ft_sub_vectors(origin, &sphere->center);
	coeff1 = ft_dot(ray_dir, ray_dir);
	coeff2 = 2 * ft_dot(&origin_center, ray_dir);
	coeff3 = ft_dot(&origin_center, &origin_center)
			- (sphere->radius * sphere->radius);
	return (calculate_discriminant(coeff1, coeff2, coeff3));
}

t_td	cylinder_intersection(t_vct *origin, t_vct *ray_dir, t_fgrs *cylinder)
{
	t_vct		coeff;
	t_vct		orig_cntr;
	double		dirc_orig_cntr;
	double		orig_cntr_dot;

	orig_cntr = ft_sub_vectors(origin, &cylinder->center);
	coeff.x = ft_dot(ray_dir, ray_dir);
	coeff.y = ft_dot(ray_dir, &cylinder->dir);
	coeff.z = ft_dot(ray_dir, &orig_cntr);
	dirc_orig_cntr = ft_dot(&orig_cntr, &cylinder->dir);
	orig_cntr_dot = ft_dot(&orig_cntr, &orig_cntr);
	coeff.x = coeff.x - (coeff.y * coeff.y);
	coeff.y = 2 * (coeff.z - coeff.y * dirc_orig_cntr);
	coeff.z = orig_cntr_dot - (dirc_orig_cntr * dirc_orig_cntr)
				- (cylinder->radius * cylinder->radius);
	return (calculate_discriminant(coeff.x, coeff.y, coeff.z));
}

t_td	cone_intersection(t_vct *origin, t_vct *ray_dir, t_fgrs *cone)
{
	t_vct		coeff;
	double		rad;
	t_vct		orig_cntr;
	double		dirc_orig_cntr;
	double		orig_cntr_dot;

	orig_cntr = ft_sub_vectors(origin, &cone->center);
	rad = tan((cone->angl * M_PI / 180.0) / 2.0);
	coeff.x = ft_dot(ray_dir, ray_dir);
	coeff.y = ft_dot(ray_dir, &cone->dir);
	coeff.z = ft_dot(ray_dir, &orig_cntr);
	dirc_orig_cntr = ft_dot(&orig_cntr, &cone->dir);
	orig_cntr_dot = ft_dot(&orig_cntr, &orig_cntr);
	coeff.x = coeff.x - (1 + rad * rad) * (coeff.y * coeff.y);
	coeff.y = 2 * (coeff.z - (1 + rad * rad) * coeff.y * dirc_orig_cntr);
	coeff.z = orig_cntr_dot - (1 + rad * rad)
			* (dirc_orig_cntr * dirc_orig_cntr);
	return (calculate_discriminant(coeff.x, coeff.y, coeff.z));
}

t_td	plane_intersection(t_vct *origin, t_vct *ray_dir, t_fgrs *plane)
{
	t_vct	orig_cntr;
	double	dvsn;
	double	dirc_orig_cntr;

	if ((dvsn = ft_dot(ray_dir, &plane->dir)) != 0)
	{
		orig_cntr = ft_sub_vectors(origin, &plane->center);
		dirc_orig_cntr = ft_dot(&orig_cntr, &plane->dir);
		return ((t_td) {-dirc_orig_cntr / dvsn, 0});
	}
	else
	{
		return ((t_td){(double)INFINITY, (double)INFINITY});
	}
}
