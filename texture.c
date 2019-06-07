/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:34:03 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/08 01:12:59 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <SDL.h>

static int		create_texture_from_surface(t_wolf *data)
{
	int			i;
	SDL_Surface	*tmp[4];

	i = 0;
	while (i < 4)
	{
		tmp[i] = SDL_ConvertSurfaceFormat(data->surfaces[i]
				, SDL_PIXELFORMAT_ARGB8888, 0);
		i++;
	}
	i = 0;
	while (i < 4)
		SDL_FreeSurface(data->surfaces[i++]);
	i = 0;
	while (i < 4)
	{
		data->surfaces[i] = tmp[i];
		i++;
	}
	return (0);
}

int				load_textures(t_wolf *data)
{
	if (!(data->surfaces[0] = SDL_LoadBMP("./textures/front.bmp")))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load texture: %s"
			, SDL_GetError());
		return (leave_sdl_and_program(data, 1));
	}
	if (!(data->surfaces[1] = SDL_LoadBMP("./textures/right.bmp")))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load texture: %s"
			, SDL_GetError());
		return (leave_sdl_and_program(data, 1));
	}
	if (!(data->surfaces[2] = SDL_LoadBMP("./textures/back.bmp")))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load texture: %s"
			, SDL_GetError());
		return (leave_sdl_and_program(data, 1));
	}
	if (!(data->surfaces[3] = SDL_LoadBMP("./textures/left.bmp")))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load texture: %s"
			, SDL_GetError());
		return (leave_sdl_and_program(data, 1));
	}
	return (create_texture_from_surface(data));
}
