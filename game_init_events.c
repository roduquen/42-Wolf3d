/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 09:33:13 by roduquen          #+#    #+#             */
/*   Updated: 2019/07/15 21:14:59 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <SDL.h>
#include "libft.h"

void			init_events(t_wolf *data)
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

void			create_string_map(char *str, char number[], int nb)
{
	int		i;

	i = 0;
	while (str[i] != '1')
	{
		number[i] = str[i];
		i++;
	}
	number[i++] = nb;
	while (str[i])
	{
		number[i] = str[i];
		i++;
	}
	number[i] = 0;
}

static void		init_player_position(t_wolf *data)
{
	int			i;
	int			j;

	i = 0;
	while (data->board[i])
	{
		j = 0;
		while (data->board[i][j])
		{
			if (ft_memchr("^><v", data->board[i][j], 4))
			{
				data->camera.position.x = i + 0.5;
				data->camera.position.y = j + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
}

void			init_game(t_wolf *data)
{
	int			i;
	char		number[100];

	number[0] = data->actual_new_game + '1';
	data->actual_floor = 0;
	create_string_map("./maps/wolfenstein/episode1/floor1", number, number[0]);
	i = 0;
	if (data->board)
	{
		while (data->board[i])
			free(data->board[i++]);
		free(data->board);
	}
	free(data->map);
	data->map = NULL;
	data->board = NULL;
	if (parsing_maps(data, number))
		exit(1);
	data->state = 6;
	init_player_position(data);
}

void			init_floor_change(t_wolf *data)
{
	int			i;
	char		number[100];
	t_door		*tmp;

	data->actual_floor++;
	while (data->doors)
	{
		tmp = data->doors;
		data->doors = data->doors->next;
		free(tmp);
	}
	ft_strcpy(number, "./maps/wolfenstein/episode1/floor1");
	number[ft_strlen(number) - 1] = data->actual_floor + 47;
	i = 0;
	while (data->board[i])
		free(data->board[i++]);
	free(data->board);
	free(data->map);
	data->board = NULL;
	data->map = NULL;
	if (parsing_maps(data, number))
		exit(1);
	data->state = 6;
	init_player_position(data);
}
