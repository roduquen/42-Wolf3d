/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_game_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 12:47:47 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/10 16:25:40 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	door_opening_system(t_wolf *data, t_vec2d pos)
{
	if (pos.x - 1 > 0 && data->board[(int)pos.x - 1][(int)pos.y] == '0')
	{
		data->board[(int)pos.x - 1][(int)pos.y] = '1';
	}
	if (pos.x + 1 < data->map_width && data->board[(int)pos.x + 1][(int)pos.y] == '0')
	{
		data->board[(int)pos.x + 1][(int)pos.y] = '1';
	}
	if (pos.y - 1 > 0 && data->board[(int)pos.x][(int)pos.y - 1] == '0')
	{
		data->board[(int)pos.x][(int)pos.y - 1] = '1';
	}
	if (pos.y + 1 < data->map_height && data->board[(int)pos.x][(int)pos.y + 1] == '0')
	{
		data->board[(int)pos.x][(int)pos.y + 1] = '1';
	}
}

void		active_commands(t_wolf *data, t_vec2d pos)
{
	if (pos.x - 1 > 0 && data->board[(int)pos.x - 1][(int)pos.y] == 'l')
	{
		data->board[(int)pos.x - 1][(int)pos.y] = 'm';
		data->actual_new_game = 1;
		init_game(data);
	}
	else if (pos.x - 1 > 0 && data->board[(int)pos.x - 1][(int)pos.y] == 'm')
	{
		data->board[(int)pos.x - 1][(int)pos.y] = 'l';
		data->actual_new_game = 1;
		init_game(data);
	}
	if (pos.x + 1 < data->map_width && data->board[(int)pos.x + 1][(int)pos.y] == 'l')
	{
		data->board[(int)pos.x + 1][(int)pos.y] = 'm';
		data->actual_new_game = 1;
		init_game(data);
	}
	else if (pos.x + 1 > 0 && data->board[(int)pos.x + 1][(int)pos.y] == 'm')
	{
		data->board[(int)pos.x + 1][(int)pos.y] = 'l';
		data->actual_new_game = 1;
		init_game(data);
	}
	if (pos.y - 1 > 0 && data->board[(int)pos.x][(int)pos.y - 1] == 'l')
	{
		data->board[(int)pos.x][(int)pos.y - 1] = 'm';
		data->actual_new_game = 1;
		init_game(data);
	}
	else if (pos.y - 1 > 0 && data->board[(int)pos.x][(int)pos.y - 1] == 'm')
	{
		data->board[(int)pos.x][(int)pos.y - 1] = 'l';
		data->actual_new_game = 1;
		init_game(data);
	}
	if (pos.y + 1 < data->map_height && data->board[(int)pos.x][(int)pos.y + 1] == 'l')
	{
		data->board[(int)pos.x][(int)pos.y + 1] = 'm';
		data->actual_new_game = 1;
		init_game(data);
	}
	else if (pos.y + 1 > 0 && data->board[(int)pos.x][(int)pos.y + 1] == 'm')
	{
		data->board[(int)pos.x][(int)pos.y + 1] = 'l';
		data->actual_new_game = 1;
		init_game(data);
	}
	else
		door_opening_system(data, pos);
}
