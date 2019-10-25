/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arithmetic_a.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 21:26:38 by ykopiika          #+#    #+#             */
/*   Updated: 2019/10/08 19:34:13 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

double			ft_dot(t_vct *v1, t_vct *v2)
{
	double		result;

	result = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
	return (result);
}

t_vct			ft_sub_vectors(t_vct *v1, t_vct *v2)
{
	t_vct	result_vector;

	result_vector.x = v1->x - v2->x;
	result_vector.y = v1->y - v2->y;
	result_vector.z = v1->z - v2->z;
	return (result_vector);
}

t_vct			ft_add_vectors(t_vct *v1, t_vct *v2)
{
	t_vct	result_vector;

	result_vector.x = v1->x + v2->x;
	result_vector.y = v1->y + v2->y;
	result_vector.z = v1->z + v2->z;
	return (result_vector);
}

t_vct			ft_multiply_scalar(t_vct *v1, double scalar)
{
	t_vct	result_vector;

	result_vector.x = v1->x * scalar;
	result_vector.y = v1->y * scalar;
	result_vector.z = v1->z * scalar;
	return (result_vector);
}
