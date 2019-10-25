/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 16:30:26 by ykopiika          #+#    #+#             */
/*   Updated: 2019/10/14 18:26:21 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		put_pixel(int x, int y, Uint32 *buf, t_clr color)
{
	int win_x;
	int win_y;

	win_x = WIDTH / 2 + x;
	win_y = HEIGHT / 2 - y - 1;
	buf[win_y * WIDTH + win_x] = (color.r << 16 | color.g << 8 | color.b);
}

static void		prepare_for_lighting(t_light_calk *v, t_intrsct in, t_rt *ray)
{
	t_vct	buf;

	v->pnt = ft_multiply_scalar(&ray->dir, in.cls_trace);
	v->pnt = ft_add_vectors(&v->pnt, &ray->cmr_pos);
	figures_normal(&v->nrml, v->pnt, in, ray);
	buf = ft_multiply_scalar(&v->nrml, INTRSCT_EPSILON);
	v->pnt = ft_add_vectors(&v->pnt, &buf);
	ray->dir = ft_multiply_scalar(&ray->dir, -1);
}

static void		color_adjustment(t_light_calk *l_calc, t_fgrs *clsst_fgrs)
{
	t_vct	white;
	t_vct	def_col;
	t_vct	spe_col;
	t_vct	tmp;

	white = (t_vct){255.0, 255.0, 255.0};
	def_col = ft_multiply_scalar(&clsst_fgrs->color, l_calc->intens_defus);
	spe_col = ft_multiply_scalar(&white, l_calc->intens_specul);
	tmp = ft_add_vectors(&def_col, &spe_col);
	l_calc->color = ft_vector_to_color(&tmp);
}

static t_clr	ray_tracing(t_rt *ray, t_fgrs *figure,
							t_lght_lst *lght)
{
	t_light_calk		l_calc;
	t_intrsct			intrsct;

	intrsct.cls_trace = INF;
	intrsct.clsst_fgrs = NULL;
	ft_bzero(&l_calc, sizeof(t_light_calk));
	l_calc.lights = lght;
	l_calc.figures = figure;
	which_figure_closer(figure, &intrsct, ray);
	if (intrsct.clsst_fgrs == NULL)
		return ((t_clr){9, 10, 10, 255});
	prepare_for_lighting(&l_calc, intrsct, ray);
	lighting_calculate(&l_calc, &ray->dir, intrsct.clsst_fgrs);
	color_adjustment(&l_calc, intrsct.clsst_fgrs);
	return (l_calc.color);
}

void			iterate_every_pixel(t_sdl *sdl, t_fgrs *fgrs,
									t_lght_lst *lght, t_data *d)
{
	int		y;
	int		x;
	Uint32	*buf;
	t_clr	color;
	t_rt	ray;

	ray.cmr_pos = d->cmr_pos;
	ray.t_max = INF;
	ray.t_min = 1;
	buf = sdl->surf_win->pixels;
	y = -HEIGHT / 2 - 1;
	while (++y < HEIGHT / 2)
	{
		x = -WIDTH / 2 - 1;
		while (++x < WIDTH / 2)
		{
			ray.dir = (t_vct){x * 1.5 / WIDTH, y * 1. / HEIGHT, 1};
			camera_rotate(&ray.dir, &d->rotate_rad);
			color = ray_tracing(&ray, fgrs, lght);
			put_pixel(x, y, buf, color);
		}
	}
}
