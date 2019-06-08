/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 03:49:49 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/08 01:46:44 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <SDL.h>
#include "libft.h"
#include <stdio.h>

static void	sdl_events_hook(t_wolf *data)
{
	if (data->event.type == SDL_QUIT)
		data->running = SDL_FALSE;
	else if (data->event.type == SDL_KEYDOWN && data->event.key.repeat == 0)
	{
		if (data->event.key.keysym.sym == SDLK_ESCAPE)
			data->running = SDL_FALSE;
		else
			camera_downkey_event(data);
	}
	else if (data->event.type == SDL_KEYUP && data->event.key.repeat == 0)
		camera_upkey_event(data);
	else if (data->event.type == SDL_MOUSEMOTION)
		camera_mouse_event(data);
}

static void	frame_calculator(unsigned int actual, t_wolf *data)
{
	static unsigned int	frame = 0;
	static unsigned int	time = 0;

	if (actual - time > 1000)
	{
		data->camera.move_speed = 5.0 / frame;
		data->camera.angle_speed = 3.0 / frame;
		printf("FPS :: %d\n", frame);
		frame = 0;
		time = actual;
	}
	frame++;
}

int			commands(t_wolf *data)
{
	int				test;
	t_vec2d			tmp;

	while (data->running)
	{
		while (SDL_PollEvent(&data->event))
			sdl_events_hook(data);
		tmp = data->camera.direction;
		camera_carry_event(data, tmp);
		if (SDL_LockTexture(data->texture, NULL, (void**)&data->texturetab
				, &test))
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION
				, "Couldn't lock texture: %s", SDL_GetError());
			return (1);
		}
		ft_memset(data->texturetab, 0, data->win_width * data->win_height);
		if (raycasting(data))
			return (1);
		SDL_UnlockTexture(data->texture);
		SDL_RenderCopy(data->renderer, data->texture, NULL, NULL);
		SDL_RenderPresent(data->renderer);
		frame_calculator(SDL_GetTicks(), data);
	}
	return (0);
}
