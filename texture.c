/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:34:03 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/09 07:25:43 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <SDL.h>

static int		create_texture_from_surface(t_wolf *data)
{
	int			i;
	SDL_Surface	*tmp;

	i = 0;
	while (i < TEXTURE_NB + SPRITE_NB)
	{
		tmp = SDL_ConvertSurfaceFormat(data->surfaces[i]
				, SDL_PIXELFORMAT_ARGB8888, 0);
		SDL_FreeSurface(data->surfaces[i]);
		data->surfaces[i++] = tmp;
	}
	return (0);
}

int				load_textures(t_wolf *data)
{
	int			i;

	i = -1;
	add_textures_path(data);
	while (++i < TEXTURE_NB)
	{
		if (!(data->surfaces[i] = SDL_LoadBMP(data->texture_path[i])))
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION
				, "Couldn't load texture: %s, %d", SDL_GetError(), i);
			return (leave_sdl_and_program(data, 1));
		}
	}
	while (i < TEXTURE_NB + SPRITE_NB)
	{
		if (!(data->surfaces[i] = SDL_LoadBMP(
						data->sprite_path[i - TEXTURE_NB])))
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION
				, "Couldn't load texture: %s", SDL_GetError());
			return (leave_sdl_and_program(data, 1));
		}
		i++;
	}
	return (create_texture_from_surface(data));
}
