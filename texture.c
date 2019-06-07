/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:34:03 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/07 14:36:28 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <SDL.h>

static int		create_last_textures(t_wolf *data)
{
	if (!(data->walls[3] = SDL_CreateTextureFromSurface(data->renderer
					, data->surfaces[3])))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION
			, "Couldn't create texture from surface: %s", SDL_GetError());
		return (leave_sdl_and_program(data, 1));
	}
	return (0);
}

static int		create_texture_from_surface(t_wolf *data)
{
	if (!(data->walls[0] = SDL_CreateTextureFromSurface(data->renderer
					, data->surfaces[0])))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION
			, "Couldn't create texture from surface: %s", SDL_GetError());
		return (leave_sdl_and_program(data, 1));
	}
	if (!(data->walls[1] = SDL_CreateTextureFromSurface(data->renderer
					, data->surfaces[1])))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION
			, "Couldn't create texture from surface: %s", SDL_GetError());
		return (leave_sdl_and_program(data, 1));
	}
	if (!(data->walls[2] = SDL_CreateTextureFromSurface(data->renderer
					, data->surfaces[2])))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION
			, "Couldn't create texture from surface: %s", SDL_GetError());
		return (leave_sdl_and_program(data, 1));
	}
	return (create_last_textures(data));
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
