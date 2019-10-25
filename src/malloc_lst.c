/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:30:52 by ykopiika          #+#    #+#             */
/*   Updated: 2019/10/08 19:16:11 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_lght_lst	*malloc_new_lght(t_lght_lst *lght)
{
	t_lght_lst *tmp;

	tmp = (t_lght_lst *)malloc(sizeof(t_lght_lst));
	if (!tmp)
		print_error(ERR_MALLOC, -1);
	else
	{
		tmp->type = NON;
		tmp->pos = (t_vct) {0, 0, 0};
		tmp->intensity = 0;
		tmp->next = lght;
	}
	return (tmp);
}

t_lght_lst			*malloc_lght(t_lght_lst *lght)
{
	if (!lght)
	{
		if (!(lght = (t_lght_lst *)malloc(sizeof(t_lght_lst))))
			print_error(ERR_MALLOC, -1);
		else
		{
			lght->type = NON;
			lght->pos = (t_vct) {0, 0, 0};
			lght->intensity = 0;
			lght->next = NULL;
			return (lght);
		}
	}
	else
		return (malloc_new_lght(lght));
	return (NULL);
}

static t_fgrs		*malloc_new_fgrs(t_fgrs *fgr)
{
	t_fgrs *tmp;

	tmp = (t_fgrs *)malloc(sizeof(t_fgrs));
	if (!tmp)
		print_error(ERR_MALLOC, -1);
	else
	{
		tmp->type = NON;
		tmp->center = (t_vct) {0, 0, 0};
		tmp->radius = 0;
		tmp->color = (t_vct) {255, 255, 255};
		tmp->specul = 0;
		tmp->next = fgr;
	}
	return (tmp);
}

t_fgrs				*malloc_fgrs(t_fgrs *fgr)
{
	t_fgrs *tmp;

	tmp = NULL;
	if (!fgr)
	{
		if (!(fgr = (t_fgrs *)malloc(sizeof(t_fgrs))))
			print_error(ERR_MALLOC, -1);
		else
		{
			fgr->type = NON;
			fgr->center = (t_vct) {0, 0, 0};
			fgr->radius = 0;
			fgr->color = (t_vct) {255, 255, 255};
			fgr->specul = 0;
			fgr->next = NULL;
			return (fgr);
		}
	}
	else
		return (malloc_new_fgrs(fgr));
	return (tmp);
}
