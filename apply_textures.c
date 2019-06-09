/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <roduquen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:41:44 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/09 19:28:11 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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
	apply_textures(thread, thread->data->board[thread->ray.x_map]
		[thread->ray.y_map] - 'a', i);
	apply_sprites(thread, thread->data->board[thread->ray.x_map]
		[thread->ray.y_map] - 'A' + TEXTURE_NB, i);
}

void			apply_textures(t_thread *thread, int type, int i)
{
	double			tmp;
	double			test;

	test = (thread->ray.height + thread->data->win_height
			- (thread->data->win_height - thread->ray.height)) / 2;
	if (thread->ray.side == 0)
		thread->ray.x_wall = thread->data->camera.position.y + thread->ray.orto
			* thread->ray.direction.y;
	else
		thread->ray.x_wall = thread->data->camera.position.x + thread->ray.orto
			* thread->ray.direction.x;
	thread->ray.x_wall -= (int)thread->ray.x_wall;
	thread->ray.x_tex = (int)(thread->ray.x_wall * 64.0);
	if (thread->ray.side == 0 && thread->ray.direction.x > 0)
		thread->ray.x_tex = 64 - 1 - thread->ray.x_tex;
	else if (thread->ray.side == 1 && thread->ray.direction.y < 0)
		thread->ray.x_tex = 64 - 1 - thread->ray.x_tex;
	tmp = i - WIN_HEIGHT / 2 + test / 2;
	thread->ray.y_tex = tmp * 64 / test;
	thread->data->texturetab[i * thread->data->win_width
		+ thread->num] = ((unsigned int*)thread->data->surfaces[type]->pixels)
		[(int)(64 * thread->ray.y_tex + thread->ray.x_tex)];
}
