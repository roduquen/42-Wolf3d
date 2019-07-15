/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_leave_sdl.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 09:49:04 by roduquen          #+#    #+#             */
/*   Updated: 2019/07/15 21:15:17 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "wolf.h"

static int	init_texture(t_wolf *data)
{
	if (!(data->texture = SDL_CreateTexture(data->renderer
					, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING
					, WIDTH, HEIGHT)))
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
	if (load_textures(data))
		return (1);
	return (0);
}

static void	init_camera_pos_and_direction(t_wolf *data, int line, int column)
{
	data->camera.position = (t_vec2d){line + 0.5, column + 0.5};
	if (data->board[line][column] == '^')
		data->camera.angle = 90.0;
	else if (data->board[line][column] == '<')
		data->camera.angle = 180.0;
	else if (data->board[line][column] == 'v')
		data->camera.angle = 270.0;
	else if (data->board[line][column] == '>')
		data->camera.angle = 0.0;
	data->camera.direction = vec2d_rotate(vec2d(0, 1)
			, to_radian(data->camera.angle));
	data->camera.plane = vec2d_scalar(vec2d_rotate(vec2d(1, 0)
			, to_radian(data->camera.angle)), 2.0 / 3.0);
	data->board[line][column] = '.';
	data->win_height = HEIGHT;
	data->win_width = WIDTH;
	data->camera.move_speed = 0.1;
	data->camera.angle_speed = 0.05;
	full_background_tab(data);
}

void		init_data_and_camera(t_wolf *data)
{
	int			i;
	int			line;
	int			column;

	i = 0;
	line = 0;
	column = 0;
	while (data->board[line])
	{
		column = 0;
		while (data->board[line][column])
		{
			if (data->board[line][column] == '^' || data->board[line][column]
				== '<' || data->board[line][column] == '>'
				|| data->board[line][column] == 'v')
				break ;
			column++;
		}
		if (data->board[line][column] == '^' || data->board[line][column]
			== '<' || data->board[line][column] == '>'
			|| data->board[line][column] == 'v')
			break ;
		line++;
	}
	init_camera_pos_and_direction(data, line, column);
}

int			init_sdl_and_program(t_wolf *data)
{
	data->running = SDL_TRUE;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s"
				, SDL_GetError());
		return (1);
	}
	if (!(data->window = SDL_CreateWindow("Wolfenstein", SDL_WINDOWPOS_CENTERED
					, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT
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
	SDL_SetRelativeMouseMode(SDL_TRUE);
	return (init_texture(data));
}
