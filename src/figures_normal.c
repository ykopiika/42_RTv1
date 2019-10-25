/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 13:21:35 by ykopiika          #+#    #+#             */
/*   Updated: 2019/10/14 17:01:07 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	cone_normal(t_vct *dst, t_vct point,
									t_intrsct in, t_rt *ray)
{
	t_calc	var;
	double	coef;

	var = (t_calc){0, 0, 0, (t_vct){0, 0, 0}, (t_vct){0, 0, 0}};
	if (in.clsst_fgrs->type == CONE)
	{
		var.orig_cntr = ft_sub_vectors(&ray->cmr_pos, &in.clsst_fgrs->center);
		var.pnt_cntr = ft_sub_vectors(&point, &in.clsst_fgrs->center);
		var.dir = ft_dot(&ray->dir, &in.clsst_fgrs->dir);
		var.dirc_orig_cntr = ft_dot(&var.orig_cntr, &in.clsst_fgrs->dir);
		var.scalar_m = var.dir * in.cls_trace + var.dirc_orig_cntr;
		coef = tan((in.clsst_fgrs->angl * M_PI / 180.0) / 2.0);
		*dst = ft_multiply_scalar(&in.clsst_fgrs->dir, (1 + coef * coef));
		*dst = ft_multiply_scalar(dst, var.scalar_m);
		*dst = ft_sub_vectors(&var.pnt_cntr, dst);
	}
}

void		figures_normal(t_vct *dst, t_vct point, t_intrsct in, t_rt *ray)
{
	t_calc	var;

	var = (t_calc){0, 0, 0, (t_vct){0, 0, 0}, (t_vct){0, 0, 0}};
	if (in.clsst_fgrs->type == SPHERE)
		*dst = ft_sub_vectors(&point, &in.clsst_fgrs->center);
	if (in.clsst_fgrs->type == PLANE)
	{
		if (ft_dot(&ray->dir, &in.clsst_fgrs->dir) > 0.0)
			*dst = ft_multiply_scalar(&in.clsst_fgrs->dir, -1.0);
		else
			*dst = in.clsst_fgrs->dir;
	}
	if (in.clsst_fgrs->type == CYLINDER)
	{
		var.orig_cntr = ft_sub_vectors(&ray->cmr_pos, &in.clsst_fgrs->center);
		var.pnt_cntr = ft_sub_vectors(&point, &in.clsst_fgrs->center);
		var.dir = ft_dot(&ray->dir, &in.clsst_fgrs->dir);
		var.dirc_orig_cntr = ft_dot(&var.orig_cntr, &in.clsst_fgrs->dir);
		var.scalar_m = var.dir * in.cls_trace + var.dirc_orig_cntr;
		*dst = ft_multiply_scalar(&in.clsst_fgrs->dir, var.scalar_m);
		*dst = ft_sub_vectors(&var.pnt_cntr, dst);
	}
	cone_normal(dst, point, in, ray);
	ft_nrmlz_vector(dst);
}
