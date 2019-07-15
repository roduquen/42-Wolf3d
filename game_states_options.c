/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_states_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 00:37:55 by roduquen          #+#    #+#             */
/*   Updated: 2019/07/15 21:15:07 by roduquen         ###   ########.fr       */
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

void	game_options_sound(t_wolf *data)
{
	while (SDL_PollEvent(&data->event))
	{
		if (data->event.type == SDL_KEYDOWN && data->event.key.repeat == 0)
		{
			if (data->event.key.keysym.sym == SDLK_UP)
				data->actual_sound--;
			else if (data->event.key.keysym.sym == SDLK_DOWN)
				data->actual_sound++;
			else if (data->event.key.keysym.sym == SDLK_ESCAPE)
				data->state = 1;
		}
	}
	if (data->actual_sound < 0)
		data->actual_sound = 1;
	if (data->actual_sound >= 2)
		data->actual_sound = 0;
	SDL_RenderCopy(data->renderer, data->menu[data->actual_sound + 40], NULL
		, NULL);
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
