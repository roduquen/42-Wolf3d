/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:29:18 by roduquen          #+#    #+#             */
/*   Updated: 2019/07/15 21:14:52 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdlib.h>

static int		add_elem_to_door(t_wolf *data, int x, int y)
{
	t_door		*new;
	t_door		*tmp;

	if (!(new = (t_door*)malloc(sizeof(t_door))))
		return (1);
	new->time = SDL_GetTicks();
	new->x = x;
	new->y = y;
	new->next = NULL;
	if (!data->doors)
		data->doors = new;
	else
	{
		tmp = data->doors;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

void			close_door(t_wolf *data)
{
	t_door			*tmp;
	unsigned int	time;

	time = SDL_GetTicks();
	while (data->doors)
	{
		if (time - data->doors->time > 5000)
		{
			if (data->doors->x == (int)data->camera.position.x
				&& data->doors->y == (int)data->camera.position.y)
				break ;
			data->board[data->doors->x][data->doors->y] = '0';
			tmp = data->doors;
			data->doors = data->doors->next;
			free(tmp);
		}
		else
			break ;
	}
}

void			doors_move(t_wolf *data, int x, int y)
{
	data->board[x][y] = '.';
	if (add_elem_to_door(data, x, y))
		data->board[x][y] = '0';
}
