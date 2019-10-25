/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arithmetic_b.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:32:55 by ykopiika          #+#    #+#             */
/*   Updated: 2019/10/08 19:34:13 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_clr			ft_vector_to_color(t_vct *v)
{
	if (v->x > 255.0 || v->x < 0.0)
		v->x = (v->x < 0.0) ? 0.0 : 255.0;
	if (v->y > 255.0 || v->y < 0.0)
		v->y = (v->y < 0.0) ? 0.0 : 255.0;
	if (v->z > 255.0 || v->z < 0.0)
		v->z = (v->z < 0.0) ? 0.0 : 255.0;
	return ((t_clr){(int)v->x, (int)v->y, (int)v->z, 255});
}

double			ft_len_vector(t_vct *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

void			ft_nrmlz_vector(t_vct *vector)
{
	double		vct_len;

	vct_len = ft_len_vector(vector);
	if (vct_len > 0.0)
		*vector = ft_multiply_scalar(vector, 1. / vct_len);
}
