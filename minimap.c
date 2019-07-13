/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 19:56:27 by roduquen          #+#    #+#             */
/*   Updated: 2019/07/13 20:02:42 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int		add_minimap_color(t_thread *thread, int i)
{
	int			pos[2];

	pos[0] = (int)thread->data->camera.position.x - thread->num / 16 + 8;
	pos[1] = (int)thread->data->camera.position.y - i / 16 + 8;
	if (pos[0] < 0 || pos[1] < 0)
		return (0x123456);
	if (pos[1] >= thread->data->map_width || pos[0] >= thread->data->map_height)
		return (0x123456);
	if ((thread->data->board[pos[0]][pos[1]] >= '1'
				&& thread->data->board[pos[0]][pos[1]] <= '9')
			|| thread->data->board[pos[0]][pos[1]] == 'k')
		return (0x7F7F7F);
	if (thread->data->board[pos[0]][pos[1]] != '.'
			&& thread->data->board[pos[0]][pos[1]] != '0')
		return (0x654987);
	if (thread->data->board[pos[0]][pos[1]] == '0')
		return (0x789456);
	return (0);
}

void			add_map(t_thread *thread, int i, int ret)
{
	if (i >= 128 && i < 143 && thread->num >= 128 && thread->num < 143)
		thread->data->texturetab[ret] = 0xFF0000;
	else if (i % 16 != 15 && thread->num % 16 != 15 && i != 0
			&& thread->num != 0)
		thread->data->texturetab[ret] = add_minimap_color(thread, i);
	else
		thread->data->texturetab[ret] = 0xFFFFFF;
}
