/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_calculate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 20:06:20 by ykopiika          #+#    #+#             */
/*   Updated: 2019/10/14 16:46:37 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		intersect_for_shadow(t_fgrs *figure, t_intrsct *in, t_rt *sh)
{
	t_td	t;

	t = (t_td){0, 0};
	in->clsst_fgrs = NULL;
	in->cls_trace = INF;
	while (figure)
	{
		if (figure->type == SPHERE)
			t = sphere_intersection(&sh->cmr_pos, &sh->dir, figure);
		if (figure->type == CONE)
			t = cone_intersection(&sh->cmr_pos, &sh->dir, figure);
		if (figure->type == CYLINDER)
			t = cylinder_intersection(&sh->cmr_pos, &sh->dir, figure);
		if (figure->type == PLANE)
			t = plane_intersection(&sh->cmr_pos, &sh->dir, figure);
		if ((in_diapason(t.t1, sh->t_min, sh->t_max)) && (t.t1 < in->cls_trace))
			*in = (t_intrsct){.cls_trace = t.t1, .clsst_fgrs = figure};
		if ((in_diapason(t.t2, sh->t_min, sh->t_max)) && (t.t2 < in->cls_trace))
			*in = (t_intrsct){.cls_trace = t.t2, .clsst_fgrs = figure};
		figure = figure->next;
	}
}

static void		calculate_refl(t_light_calk *v, t_vct *l_dir,
								t_vct *ray_dir, t_fgrs *clsst_fgrs)
{
	t_vct		refl;
	double		r_dot_v;

	refl = ft_multiply_scalar(&v->nrml, 2);
	refl = ft_multiply_scalar(&refl, ft_dot(&v->nrml, l_dir));
	refl = ft_sub_vectors(&refl, l_dir);
	r_dot_v = ft_dot(&refl, ray_dir);
	if (r_dot_v > 0)
	{
		v->intens_specul += v->lights->intensity
				* pow(r_dot_v / (ft_len_vector(&refl)
				* ft_len_vector(ray_dir)), clsst_fgrs->specul);
	}
}

static void		shadow_calculate(t_fgrs *clsst_fgrs, t_light_calk *v,
									t_rt *sh, t_vct *ray_dir)
{
	t_intrsct	shdw;
	double		n_dot_l;

	shdw = (t_intrsct){0.0, NULL};
	intersect_for_shadow(v->figures, &shdw, sh);
	if (shdw.clsst_fgrs == NULL)
	{
		if ((n_dot_l = ft_dot(&v->nrml, &sh->dir)) > 0)
			v->intens_defus += (v->lights->intensity * n_dot_l) /
					((ft_len_vector(&v->nrml) * ft_len_vector(&sh->dir)));
		if (clsst_fgrs->specul > 0.0)
			calculate_refl(v, &sh->dir, ray_dir, clsst_fgrs);
	}
}

static t_vct	choose_type(double *tmax, t_light_calk *v)
{
	t_vct	l_dir;

	if (v->lights->type == DIRECTIONAL)
	{
		l_dir = v->lights->pos;
		*tmax = INF;
	}
	else
	{
		l_dir = ft_sub_vectors(&v->lights->pos, &v->pnt);
		*tmax = 1.0;
	}
	return (l_dir);
}

void			lighting_calculate(t_light_calk *v, t_vct *ray_dir,
									t_fgrs *closest_sphere)
{
	t_vct	l_dir;
	t_rt	sh;
	double	tmax;

	while (v->lights)
	{
		if (v->lights->type == AMBIENT)
			v->intens_defus += v->lights->intensity;
		else
		{
			l_dir = choose_type(&tmax, v);
			sh = (t_rt){.cmr_pos = v->pnt, .dir = l_dir,
						.t_min = INTRSCT_EPSILON, .t_max = tmax};
			shadow_calculate(closest_sphere, v, &sh, ray_dir);
		}
		v->lights = v->lights->next;
	}
}
