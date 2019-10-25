/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_figure_closer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 18:28:17 by ykopiika          #+#    #+#             */
/*   Updated: 2019/10/14 16:46:37 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

_Bool	in_diapason(double nb, double min, double max)
{
	return ((nb > min) && (nb < max));
}

void	which_figure_closer(t_fgrs *figure, t_intrsct *in, t_rt *r)
{
	t_td	t;

	t = (t_td){0, 0};
	in->clsst_fgrs = NULL;
	in->cls_trace = INF;
	while (figure)
	{
		if (figure->type == SPHERE)
			t = sphere_intersection(&r->cmr_pos, &r->dir, figure);
		if (figure->type == PLANE)
			t = plane_intersection(&r->cmr_pos, &r->dir, figure);
		if (figure->type == CYLINDER)
			t = cylinder_intersection(&r->cmr_pos, &r->dir, figure);
		if (figure->type == CONE)
			t = cone_intersection(&r->cmr_pos, &r->dir, figure);
		if ((in_diapason(t.t1, r->t_min, r->t_max)) && (t.t1 < in->cls_trace))
			*in = (t_intrsct){.cls_trace = t.t1, .clsst_fgrs = figure};
		if ((in_diapason(t.t2, r->t_min, r->t_max)) && (t.t2 < in->cls_trace))
			*in = (t_intrsct){.cls_trace = t.t2, .clsst_fgrs = figure};
		figure = figure->next;
	}
}
