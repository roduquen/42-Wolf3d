/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 08:01:50 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/09 13:18:06 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <SDL.h>
#include "libft.h"

void	game_options_control(t_wolf *data)
{
	while (SDL_PollEvent(&data->event))
	{
		if (data->event.type == SDL_KEYDOWN && data->event.key.repeat == 0)
		{
			if (data->event.key.keysym.sym == SDLK_UP)
				data->actual_control--;
			else if (data->event.key.keysym.sym == SDLK_DOWN)
				data->actual_control++;
			else if (data->event.key.keysym.sym == SDLK_ESCAPE)
				data->state = 1;
		}
	}
	if (data->actual_control < 0)
		data->actual_control = 1;
	if (data->actual_control >= 2)
		data->actual_control = 0;
	SDL_RenderCopy(data->renderer, data->menu[data->actual_control + 38], NULL
		, NULL);
	SDL_RenderPresent(data->renderer);
}

void	game_start(t_wolf *data)
{
	while (SDL_PollEvent(&data->event))
		if (data->event.type == SDL_KEYDOWN)
			data->state = 1;
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
			else if (data->event.key.keysym.sym == SDLK_ESCAPE)
				data->running = 0;
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

void	game_options_new_game(t_wolf *data)
{
	while (SDL_PollEvent(&data->event))
	{
		if (data->event.type == SDL_KEYDOWN && data->event.key.repeat == 0)
		{
			if (data->event.key.keysym.sym == SDLK_UP)
				data->actual_new_game--;
			else if (data->event.key.keysym.sym == SDLK_DOWN)
				data->actual_new_game++;
			else if (data->event.key.keysym.sym == SDLK_ESCAPE)
				data->state = 1;
			else if (data->event.key.keysym.sym == SDLK_RETURN)
				init_game(data);
		}
	}
	if (data->actual_new_game < 0)
		data->actual_new_game = 6;
	if (data->actual_new_game >= 7)
		data->actual_new_game = 0;
	SDL_RenderCopy(data->renderer, data->menu[data->actual_new_game + 31], NULL
		, NULL);
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
	t_vec2d	tmp;

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
	return (0);
}
