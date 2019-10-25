/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type_count_nbrs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:09:12 by ykopiika          #+#    #+#             */
/*   Updated: 2019/10/12 17:35:43 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		cmp_begin(const char *s1, const char *s2)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	while (s1[i] != '\0' && (s1[i] == s2[i]))
		i++;
	if (i == len)
		return (1);
	return (0);
}

static int		count_number(char *str, int len, int row)
{
	int i;
	int nb;
	int dot;

	i = 0;
	nb = 0;
	while (i < len && str[i] != COMNT)
	{
		if (ft_isdigit(str[i]))
		{
			nb++;
			dot = 0;
			while (i < len && str[i] != COMNT
					&& (ft_isdigit(str[i]) || str[i] == '.'))
				if (str[i++] == '.')
					dot++;
			if (dot > 1)
				print_error(ERR_DOT, row);
		}
		if (str[i] == COMNT)
			break ;
		i++;
	}
	return (nb);
}

static void		what_type(int *type, char *str, int row)
{
	if (cmp_begin("sphere", str) == 1)
		*type = SPHERE;
	else if (cmp_begin("plane", str) == 1)
		*type = PLANE;
	else if (cmp_begin("cone", str) == 1)
		*type = CONE;
	else if (cmp_begin("cylinder", str) == 1)
		*type = CYLINDER;
	else if (cmp_begin("ambient", str) == 1)
		*type = AMBIENT;
	else if (cmp_begin("directional", str) == 1)
		*type = DIRECTIONAL;
	else if (cmp_begin("point", str) == 1)
		*type = POINT;
	else if (cmp_begin("camera", str) == 1)
		*type = CAMERA;
	else
		print_error(ERR_LINE, row);
}

static void		check_count_nbrs(t_parse p, int *nb, t_read *read)
{
	if (p.type == SPHERE && *nb != SPHR_NBR)
		print_error(ERR_NBR, read->row);
	else if (p.type == PLANE && *nb != PLN_NBR)
		print_error(ERR_NBR, read->row);
	else if (p.type == CONE && *nb != CONE_NBR)
		print_error(ERR_NBR, read->row);
	else if (p.type == CYLINDER && *nb != CLDR_NBR)
		print_error(ERR_NBR, read->row);
	else if (p.type == AMBIENT && *nb != AMBNT_NBR)
		print_error(ERR_NBR, read->row);
	else if (p.type == POINT && *nb != PNT_NBR)
		print_error(ERR_NBR, read->row);
	else if (p.type == DIRECTIONAL && *nb != DIR_NBR)
		print_error(ERR_NBR, read->row);
	else if (p.type == CAMERA && *nb != CMR_NBR)
		print_error(ERR_NBR, read->row);
}

int				check_type_count_nbrs(char *str, int len, t_read *read, int *nb)
{
	t_parse	p;

	p.nbrs = 0;
	p.type = 0;
	while (p.nbrs < len && str[p.nbrs] != COMNT)
		p.nbrs++;
	if (p.nbrs == 0)
		return (0);
	what_type(&p.type, str, read->row);
	*nb = count_number(str, len, read->row);
	check_count_nbrs(p, nb, read);
	return (p.type);
}
