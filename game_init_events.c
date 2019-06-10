/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 09:33:13 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/10 13:55:54 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <SDL.h>
#include "libft.h"

void		init_events(t_wolf *data)
{
	if (data->options == MENU_QUIT)
		data->running = 0;
	else if (data->options == MENU_READ)
		data->state = 2;
	else if (data->options == MENU_NEW)
		data->state = 3;
	else if (data->options == MENU_CONT)
		data->state = 4;
	else if (data->options == MENU_SOUND)
		data->state = 5;
}

void		init_game(t_wolf *data)
{
	int			i;
	int			j;

	if (data->actual_new_game == 0)
	{
		free(data->board);
		free(data->map);
		parsing_maps(data, "./maps/wolfenstein/episode1/floor1");
		data->state = 6;
	}
	if (data->actual_new_game == 1)
	{
		free(data->board);
		free(data->map);
		parsing_maps(data, "./maps/wolfenstein/episode1/floor2");
		data->state = 6;
	}
	i = 0;
	while (data->board[i])
	{
		j = 0;
		while (data->board[i][j])
		{
			if (ft_strchr("^><v", data->board[i][j]))
			{
				data->camera.position.x = i;
				data->camera.position.y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}
