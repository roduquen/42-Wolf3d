/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 03:49:49 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/03 14:10:13 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <SDL.h>

static void	sdl_events_hook(t_wolf *data)
{
	if (data->event.type == SDL_QUIT)
		data->running = SDL_FALSE;
	else if (data->event.type == SDL_KEYDOWN)
	{
		if (data->event.key.keysym.sym == SDLK_ESCAPE)
			data->running = SDL_FALSE;
		else
			camera_downkey_event(data);
	}
	else if (data->event.type == SDL_KEYUP)
		camera_upkey_event(data);
	else if (data->event.type == SDL_MOUSEMOTION)
		camera_mouse_event(data);
}

static void	frame_calculator(unsigned int actual)
{
	static unsigned int	frame = 0;
	static unsigned int	time = 0;

	if (actual - time > 1000)
	{
		printf("FPS :: %d\n", frame);
		frame = 0;
		time = actual;
	}
	frame++;
}

int			commands(t_wolf *data)
{
	int				test;

	while (data->running)
	{
		if (SDL_PollEvent(&data->event))
			sdl_events_hook(data);
		camera_carry_event(data);
		if (SDL_LockTexture(data->texture, NULL, (void**)&data->texturetab
				, &test))
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION
				, "Couldn't lock texture: %s", SDL_GetError());
			return (1);
		}
		if (raycasting(data))
			return (1);
		SDL_UnlockTexture(data->texture);
		SDL_RenderCopy(data->renderer, data->texture, NULL, NULL);
		SDL_RenderPresent(data->renderer);
		frame_calculator(SDL_GetTicks());
	}
	return (0);
}
