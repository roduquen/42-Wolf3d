/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:34:03 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/09 07:59:08 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <SDL.h>

static int		convert_surface(t_wolf *data)
{
	int			i;
	SDL_Surface	*tmp;

	i = 0;
	while (i < TEXTURE_NB + SPRITE_NB + MENU_NB)
	{
		tmp = SDL_ConvertSurfaceFormat(data->surfaces[i]
				, SDL_PIXELFORMAT_ARGB8888, 0);
		SDL_FreeSurface(data->surfaces[i]);
		data->surfaces[i++] = tmp;
	}
	i = 0;
	while (i < MENU_NB)
	{
		if (!(data->menu[i] = SDL_CreateTextureFromSurface(data->renderer
						, data->surfaces[i + TEXTURE_NB + SPRITE_NB])))
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION
				, "Couldn't create texture: %s", SDL_GetError());
			return (leave_sdl_and_program(data, 1));
		}
		i++;
	}
	return (0);
}

static int		load_menu_textures(t_wolf *data, int i)
{
	while (i < TEXTURE_NB + SPRITE_NB + MENU_NB)
	{
		if (!(data->surfaces[i] = SDL_LoadBMP(
						data->menu_path[i - TEXTURE_NB - SPRITE_NB])))
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION
				, "Couldn't load texture: %s", SDL_GetError());
			return (leave_sdl_and_program(data, 1));
		}
		i++;
	}
	return (convert_surface(data));
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
	return (load_menu_textures(data, i));
}
