/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 08:01:50 by roduquen          #+#    #+#             */
/*   Updated: 2019/07/15 21:15:03 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <SDL.h>
#include "libft.h"

void	game_start(t_wolf *data)
{
	while (SDL_PollEvent(&data->event))
	{
		if (data->event.type == SDL_KEYDOWN)
			data->state = 1;
		if (data->event.key.keysym.sym == SDLK_ESCAPE
			&& data->event.key.repeat == 0)
			data->running = SDL_FALSE;
	}
	SDL_RenderCopy(data->renderer, data->menu[0], NULL, NULL);
	SDL_RenderPresent(data->renderer);
}

void	game_init(t_wolf *data)
{
	if (!data->options)
		data->options = 1;
	while (SDL_PollEvent(&data->event))
	{
		if (data->event.type == SDL_KEYDOWN && data->event.key.repeat == 0)
		{
			if (data->event.key.keysym.sym == SDLK_UP)
				data->options--;
			else if (data->event.key.keysym.sym == SDLK_DOWN)
				data->options++;
			else if (data->event.key.keysym.sym == SDLK_ESCAPE && data->board)
				data->state = 6;
			else if (data->event.key.keysym.sym == SDLK_RETURN)
				init_events(data);
		}
	}
	if (data->options < 1)
		data->options = 8;
	if (data->options >= 9)
		data->options = 1;
	SDL_RenderCopy(data->renderer, data->menu[data->options], NULL, NULL);
	SDL_RenderPresent(data->renderer);
}

void	game_options_read(t_wolf *data)
{
	while (SDL_PollEvent(&data->event))
	{
		if (data->event.type == SDL_KEYDOWN && data->event.key.repeat == 0)
		{
			if (data->event.key.keysym.sym == SDLK_LEFT)
				data->actual_read--;
			else if (data->event.key.keysym.sym == SDLK_RIGHT)
				data->actual_read++;
			else if (data->event.key.keysym.sym == SDLK_ESCAPE)
				data->state = 1;
		}
	}
	if (data->actual_read < 0)
		data->actual_read = 0;
	if (data->actual_read >= 22)
		data->actual_read = 21;
	SDL_RenderCopy(data->renderer, data->menu[data->actual_read
		+ MENU_QUIT + 1], NULL, NULL);
	SDL_RenderPresent(data->renderer);
}

int		game_running(t_wolf *data)
{
	int		test;

	if (!SDL_LockTexture(data->texture, NULL, (void**)&data->texturetab
			, &test))
	{
		SDL_UnlockTexture(data->texture);
		if (raycasting(data))
			return (1);
		SDL_RenderCopy(data->renderer, data->texture, NULL, NULL);
		SDL_RenderPresent(data->renderer);
		while (SDL_PollEvent(&data->event))
			sdl_events_hook(data);
		camera_carry_event(data, data->camera.direction);
	}
	frame_calculator(SDL_GetTicks(), data);
	return (0);
}
