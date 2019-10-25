/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 20:09:33 by ykopiika          #+#    #+#             */
/*   Updated: 2019/10/14 18:41:30 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_sdl_struct(t_data *d)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		print_error(ERR_SDL, -1);
	d->sdl.win = SDL_CreateWindow("RTv1",
					SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
					WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	if (!d->sdl.win)
		print_error(ERR_SDL, -1);
	d->sdl.surf_win = SDL_GetWindowSurface(d->sdl.win);
	if (!d->sdl.surf_win)
		print_error(ERR_SDL, -1);
}

int			main(int ac, char **av)
{
	t_data		*data;
	int			fd;

	if (ac != 2)
		print_error(ERR_USAGE, -1);
	if (!(data = (t_data*)malloc(sizeof(t_data))))
	{
		print_error(ERR_MALLOC, -1);
		return (0);
	}
	ft_bzero(data, sizeof(t_data));
	fd = open(av[1], O_RDONLY);
	validation_file(data, fd);
	close(fd);
	read_data(data);
	init_sdl_struct(data);
	iterate_every_pixel(&data->sdl, data->figures, data->lights, data);
	SDL_UpdateWindowSurface(data->sdl.win);
	game_loop(data);
	return (0);
}
