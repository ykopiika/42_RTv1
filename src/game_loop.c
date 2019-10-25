/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 15:13:45 by ykopiika          #+#    #+#             */
/*   Updated: 2019/10/14 18:53:29 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	rtv1_over(t_data *d)
{
	SDL_FreeSurface(d->sdl.surf_win);
	SDL_DestroyWindow(d->sdl.win);
	SDL_Quit();
}

static void	which_button_is_pressed(t_keys *k, int keycode, SDL_Event events)
{
	if (keycode == SDLK_KP_1)
		k->kp_1 = events.type == SDL_KEYDOWN;
	if (keycode == SDLK_KP_2)
		k->kp_2 = events.type == SDL_KEYDOWN;
	if (keycode == SDLK_KP_3)
		k->kp_3 = events.type == SDL_KEYDOWN;
	if (keycode == SDLK_KP_4)
		k->kp_4 = events.type == SDL_KEYDOWN;
	if (keycode == SDLK_KP_5)
		k->kp_5 = events.type == SDL_KEYDOWN;
	if (keycode == SDLK_KP_6)
		k->kp_6 = events.type == SDL_KEYDOWN;
}

void		game_loop(t_data *d)
{
	SDL_Event	events;
	_Bool		is_rtv1_on;
	int			key;

	is_rtv1_on = 1;
	while (is_rtv1_on)
	{
		while (SDL_PollEvent(&events))
		{
			key = events.key.keysym.sym;
			if (events.type == SDL_QUIT
				|| (events.type == SDL_KEYDOWN && key == SDLK_ESCAPE))
				is_rtv1_on = 0;
			if (events.type == SDL_KEYDOWN || events.type == SDL_KEYUP)
				which_button_is_pressed(&d->keys, key, events);
		}
		keyboard(d);
	}
	rtv1_over(d);
}
