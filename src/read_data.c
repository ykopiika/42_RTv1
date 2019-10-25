/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 16:44:03 by linux             #+#    #+#             */
/*   Updated: 2019/10/14 18:33:04 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static double	after_dot(char *str, double nbr)
{
	int		sign;
	int		i;
	double	res;

	res = 0;
	sign = 1;
	if (nbr < 0)
		sign = -1;
	i = 0;
	while (str[i] != '\0' && str[i] != COMNT && ft_isdigit(str[i]))
		i++;
	res = ft_atoi(str);
	if (res != 0)
	{
		while (--i > -1)
			res /= 10;
	}
	return (res * sign);
}

static void		check_write_value_continiue(t_data *data, const double *arr,
											t_parse *p, t_vct pos)
{
	if (p->type == PLANE)
		*p->fgrs = (t_fgrs) {PLANE, pos, 0, p->fgrs->color, (int)arr[6],
								p->fgrs->dir, 0, p->fgrs->next};
	if (p->type == CONE)
		*p->fgrs = (t_fgrs) {CONE, pos, 0, p->fgrs->color, (int)arr[7],
								p->fgrs->dir, arr[3], p->fgrs->next};
	else if (p->type == CAMERA)
	{
		data->cmr_pos = pos;
		data->rotate_rad = (t_vct){arr[3] * M_PI / 180,
									arr[4] * M_PI / 180,
									arr[5] * M_PI / 180};
	}
	else if (p->type == AMBIENT || p->type == POINT || p->type == DIRECTIONAL)
	{
		p->lghts->type = p->type;
		p->lghts->intensity = (p->type == AMBIENT) ? arr[0] : arr[3];
		min_max_double(&p->lghts->intensity, 0.0, 1.0);
		p->lghts->pos = (p->type == AMBIENT) ? (t_vct){0, 0, 0}
									: (t_vct){arr[0], arr[1], arr[2]};
	}
	value_clamp(p);
}

static void		check_write_value(t_data *data, const double *arr, t_parse *p)
{
	t_vct	pos;

	pos = (t_vct){0, 0, 0};
	if (p->type != AMBIENT)
		pos = (t_vct) {arr[0], arr[1], arr[2]};
	if (p->type == SPHERE || p->type == CYLINDER || p->type == CONE)
		p->fgrs->color = (t_vct) {(int)arr[4], (int)arr[5], (int)arr[6]};
	if (p->type == PLANE)
		p->fgrs->color = (t_vct) {(int)arr[3], (int)arr[4], (int)arr[5]};
	if (p->type == SPHERE || p->type == CYLINDER)
		*p->fgrs = (t_fgrs) {p->type, pos, arr[3], p->fgrs->color, (int)arr[7],
						(t_vct){0, 0, 0}, 0, p->fgrs->next};
	if (p->type == CONE)
		*p->fgrs = (t_fgrs) {p->type, pos, 0, p->fgrs->color, (int)arr[7],
						(t_vct){0, 0, 0}, arr[3], p->fgrs->next};
	if (p->type == CYLINDER || p->type == CONE || p->type == PLANE)
	{
		if (p->type == CYLINDER || p->type == CONE)
			p->fgrs->dir = (t_vct) {arr[8], arr[9], arr[10]};
		if (p->type == PLANE)
			p->fgrs->dir = (t_vct) {arr[7], arr[8], arr[9]};
		ft_nrmlz_vector(&p->fgrs->dir);
	}
	check_write_value_continiue(data, arr, p, pos);
}

static void		get_value_from_line(t_data *data, t_read *read, t_parse *p)
{
	t_get_val	val;
	double		arr[p->nbrs];

	val = (t_get_val){0, 0, read->len, read->line};
	while (val.i < val.len && val.str[val.i] != COMNT)
	{
		while (val.i < val.len && val.str[val.i] != COMNT
		&& !ft_isdigit(val.str[val.i]) && val.str[val.i] != '-')
			val.i++;
		if (val.i > 0 && val.str[val.i - 1] == '.' && (val.j > 0))
			arr[val.j - 1] += after_dot(&val.str[val.i], arr[val.j - 1]);
		else
		{
			arr[val.j] = ft_atoi(&val.str[val.i]);
			val.j++;
		}
		if (val.str[val.i] == '-')
			val.i++;
		while (ft_isdigit(val.str[val.i]))
			val.i++;
	}
	check_write_value(data, &arr[0], p);
}

void			read_data(t_data *data)
{
	t_read	*read;
	t_parse	p;

	read = data->read;
	while (read)
	{
		p.type = 0;
		p.nbrs = 0;
		p.type = check_type_count_nbrs(read->line, read->len, read, &p.nbrs);
		if (p.type != 0)
		{
			if (p.type == AMBIENT || p.type == POINT || p.type == DIRECTIONAL)
				data->lights = malloc_lght(data->lights);
			else if (p.type == CAMERA)
				;
			else
				data->figures = malloc_fgrs(data->figures);
			p = (t_parse){.fgrs = data->figures, .lghts = data->lights,
				.type = p.type, .nbrs = p.nbrs};
			get_value_from_line(data, read, &p);
		}
		read = read->next;
	}
}
