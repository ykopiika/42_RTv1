/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 20:35:13 by ykopiika          #+#    #+#             */
/*   Updated: 2019/10/14 18:42:02 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		keyboard(t_data *d)
{
	if (d->keys.kp_4)
		d->rotate_rad.x += 3 * M_PI / 180;
	if (d->keys.kp_1)
		d->rotate_rad.x -= 3 * M_PI / 180;
	if (d->keys.kp_5)
		d->rotate_rad.y += 3 * M_PI / 180;
	if (d->keys.kp_2)
		d->rotate_rad.y -= 3 * M_PI / 180;
	if (d->keys.kp_6)
		d->rotate_rad.z += 3 * M_PI / 180;
	if (d->keys.kp_3)
		d->rotate_rad.z -= 3 * M_PI / 180;
	if (d->keys.kp_1 || d->keys.kp_2 || d->keys.kp_3 || d->keys.kp_4
		|| d->keys.kp_5 || d->keys.kp_6)
	{
		iterate_every_pixel(&d->sdl, d->figures, d->lights, d);
		SDL_UpdateWindowSurface(d->sdl.win);
	}
}
