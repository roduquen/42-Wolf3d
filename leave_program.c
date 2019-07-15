/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 00:34:33 by roduquen          #+#    #+#             */
/*   Updated: 2019/07/15 21:15:23 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <SDL.h>

static int	free_surface_and_texture(t_wolf *data, int type)
{
	int		i;
	t_door	*tmp;

	i = 0;
	while (i < TEXTURE_NB + SPRITE_NB + MENU_NB)
	{
		if (data->surfaces[i])
			SDL_FreeSurface(data->surfaces[i]);
		i++;
	}
	i = 0;
	while (i < MENU_NB)
	{
		if (data->menu[i])
			SDL_DestroyTexture(data->menu[i]);
		i++;
	}
	while (data->doors)
	{
		tmp = data->doors;
		data->doors = data->doors->next;
		free(tmp);
	}
	return (type);
}

int			leave_sdl_and_program(t_wolf *data, int type)
{
	int			i;

	i = 0;
	if (data->texture)
		SDL_DestroyTexture(data->texture);
	if (data->renderer)
		SDL_DestroyRenderer(data->renderer);
	if (data->window)
		SDL_DestroyWindow(data->window);
	SDL_Quit();
	if (data->map)
		free(data->map);
	if (data->board)
	{
		while (data->board[i])
			free(data->board[i++]);
		free(data->board);
	}
	return (free_surface_and_texture(data, type));
}
