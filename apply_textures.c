/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:41:44 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/14 11:40:48 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"

static int		door_texture(t_thread *thread, int i)
{
	if ((thread->ray.side == 0 && thread->ray.direction.x < 0
			&& thread->ray.x_map + 1 > 0 && thread->data->board
			[thread->ray.x_map + 1][thread->ray.y_map] == '0')
		|| (thread->ray.side == 1 && thread->ray.direction.y < 0
			&& thread->ray.y_map + 1 > 0 && thread->data->board
			[thread->ray.x_map][thread->ray.y_map + 1] == '0')
		|| (thread->ray.side == 0 && thread->ray.direction.x >= 0
			&& thread->ray.x_map - 1 > 0 && thread->data->board
			[thread->ray.x_map - 1][thread->ray.y_map] == '0')
		|| (thread->ray.side == 1 && thread->ray.direction.y >= 0
			&& thread->ray.y_map - 1 > 0 && thread->data->board
			[thread->ray.x_map][thread->ray.y_map - 1] == '0'))
	{
		apply_textures(thread, 12, i);
		return (0);
	}
	return (1);
}

void			apply_right_texture(t_thread *thread, int i)
{
	if (!door_texture(thread, i))
		return ;
	if (ft_strchr("123456789", thread->data->board[thread->ray.x_map][thread->ray.y_map]))
		apply_textures(thread, 11, i);
	else if (!(ft_strchr(".0", thread->data->board[thread->ray.x_map][thread->ray.y_map])))
		apply_textures(thread, thread->data->board[thread->ray.x_map]
			[thread->ray.y_map] - 'a', i);
}

void			apply_textures(t_thread *thread, int type, int i)
{
	if (thread->ray.side == 0)
		thread->ray.x_wall = thread->data->camera.position.y + thread->ray.orto
			* thread->ray.direction.y;
	else
		thread->ray.x_wall = thread->data->camera.position.x + thread->ray.orto
			* thread->ray.direction.x;
	thread->ray.x_wall -= (int)thread->ray.x_wall;
	thread->ray.x_tex = (int)(thread->ray.x_wall * 64.0);
	if ((thread->ray.side == 0 && thread->ray.direction.x > 0)
		|| (thread->ray.side == 1 && thread->ray.direction.y < 0))
		thread->ray.x_tex = 63 - thread->ray.x_tex;
	thread->ray.y_tex = (i * 64 - WIN_HEIGHT * 32 + thread->ray.height * 32) / thread->ray.height;
	thread->data->texturetab[i * WIN_WIDTH
		+ thread->num] = ((unsigned int*)thread->data->surfaces[type]->pixels)
		[(int)(64 * thread->ray.y_tex + thread->ray.x_tex)];
}
