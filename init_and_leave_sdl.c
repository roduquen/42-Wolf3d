/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_leave_sdl.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 09:49:04 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/03 06:20:43 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "wolf.h"

int			leave_sdl_and_program(t_wolf *data, int type)
{
	if (data->texture)
		SDL_DestroyTexture(data->texture);
	if (data->renderer)
		SDL_DestroyRenderer(data->renderer);
	if (data->window)
		SDL_DestroyWindow(data->window);
	SDL_Quit();
	if (data->map)
		free(data->map);
	return (type);
}

static int	init_texture(t_wolf *data)
{
	if (!(data->texture = SDL_CreateTexture(data->renderer
				, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING
				, data->win_width, data->win_height)))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture: %s"
			, SDL_GetError());
		return (leave_sdl_and_program(data, 1));
	}
	if (SDL_ShowCursor(SDL_DISABLE) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't hide cursor: %s"
			, SDL_GetError());
		return (leave_sdl_and_program(data, 1));
	}
	return (0);
}

static void	init_camera_pos_and_direction(t_wolf *data)
{
	int			i;
	int			line;
	int			column;

	i = 0;
	line = 1;
	column = 1;
	while (data->map[i] != '^' && data->map[i] != '<' && data->map[i] != '>'
			&& data->map[i] != 'v' && data->map[i])
	{
		if (data->map[i++] == '\n' && ++line)
			column = 1;
		else
			column++;
	}
	data->camera.position = (t_vec2d){BLOCK_SIZE * column, BLOCK_SIZE * line};
	if (data->map[i - 1] == '^')
		data->camera.angle = 0.0;
	else if (data->map[i - 1] == '>')
		data->camera.angle = 90.0;
	else if (data->map[i - 1] == 'v')
		data->camera.angle = 180.0;
	else if (data->map[i - 1] == '<')
		data->camera.angle = 270.0;
	data->camera.direction = vec2d_rotate((t_vec2d){1, 0}, data->camera.angle);
}

static void	init_data_and_camera(t_wolf *data)
{
	init_camera_pos_and_direction(data);
	data->running = SDL_TRUE;
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
	data->camera.fov = (double)CAMERA_FOV;
	data->camera.alpha = (double)CAMERA_FOV / (double)WIN_WIDTH;
	data->camera.angle_speed = 25.0;
	data->camera.move_speed = 50.0;
	data->camera.ray_length = 200.0;
}

int			init_sdl_and_program(t_wolf *data)
{
	init_data_and_camera(data);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s"
			, SDL_GetError());
		return (1);
	}
	if (!(data->window = SDL_CreateWindow("Wolfenstein", SDL_WINDOWPOS_CENTERED
					, SDL_WINDOWPOS_CENTERED, 2560, 1440
					, SDL_WINDOW_FULLSCREEN)))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s"
			, SDL_GetError());
		return (leave_sdl_and_program(data, 1));
	}
	if (!(data->renderer = SDL_CreateRenderer(data->window, -1
					, SDL_RENDERER_PRESENTVSYNC)))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION
			, "Couldn't create renderer: %s", SDL_GetError());
		return (leave_sdl_and_program(data, 1));
	}
	return (init_texture(data));
}
