/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 03:49:49 by roduquen          #+#    #+#             */
/*   Updated: 2019/07/11 00:47:19 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <SDL.h>
#include "libft.h"

void		sdl_events_hook(t_wolf *data)
{
	if (data->event.type == SDL_QUIT)
		data->running = SDL_FALSE;
	else if (data->event.type == SDL_KEYDOWN && data->event.key.repeat == 0)
	{
		if (data->event.key.keysym.sym == SDLK_ESCAPE)
			data->state = 1;
		else
			camera_downkey_event(data);
		if (data->event.key.keysym.sym == SDLK_SPACE)
			active_commands(data, data->camera.position);
	}
	else if (data->event.type == SDL_KEYUP && data->event.key.repeat == 0)
		camera_upkey_event(data);
	else if (data->event.type == SDL_MOUSEMOTION)
		camera_mouse_event(data);
}

void		frame_calculator(unsigned int actual)
{
	static unsigned int	frame = 0;
	static unsigned int	time = 0;

	if (actual - time > 1000)
	{
		ft_putstr("FPS : ");
		ft_putnbr(frame);
		ft_putchar('\n');
		frame = 0;
		time = actual;
	}
	frame++;
}

int			commands(t_wolf *data)
{
	while (data->running)
	{
		if (data->state == 0)
			game_start(data);
		else if (data->state == 1)
			game_init(data);
		else if (data->state == 2)
			game_options_read(data);
		else if (data->state == 3)
			game_options_new_game(data);
		else if (data->state == 4)
			game_options_control(data);
		else if (data->state == 5)
			game_options_sound(data);
		else if (data->state == 6)
		{
			if (game_running(data))
				return (1);
		}
	}
	return (0);
}
