/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 17:10:37 by ykopiika          #+#    #+#             */
/*   Updated: 2018/12/12 17:10:41 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len_int(int n)
{
	int	r;

	if (n <= 0)
		r = 1;
	else
		r = 0;
	while (n)
	{
		r++;
		n /= 10;
	}
	return (r);
}