/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:41:44 by roduquen          #+#    #+#             */
/*   Updated: 2019/07/18 21:52:26 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"

static int		door_texture(t_thread *thread, int i, int ret)
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
		apply_textures(thread, 12, i, ret);
		return (0);
	}
	return (1);
}

void			apply_right_texture(t_thread *thread, int i, int ret)
{
	if (!door_texture(thread, i, ret))
		return ;
	if (ft_memchr("123456789", thread->data->board[thread->ray.x_map]
			[thread->ray.y_map], 9))
		apply_textures(thread, 11, i, ret);
	else if (!(ft_memchr(".0", thread->data->board[thread->ray.x_map]
				[thread->ray.y_map], 2)))
		apply_textures(thread, thread->data->board[thread->ray.x_map]
			[thread->ray.y_map] - 'a', i, ret);
}

static void		add_color_to_pixel_with_dist(t_thread *thread, int type, int i
	, int pos)
{
	int		color[3];
	double	gradient;

	pos = i * WIDTH + thread->num;
	if (thread->ray.wall_size[thread->num % NBR_THREAD] < DIST_VIEW)
	{
		thread->data->texturetab[pos] = 0;
		return ;
	}
	thread->data->texturetab[pos] =
		((unsigned int*)thread->data->surfaces[type]->pixels)
		[(int)(64 * thread->ray.y_tex + thread->ray.x_tex)];
	if (thread->ray.wall_size[thread->num % NBR_THREAD] > (HEIGHT >> 1))
		return ;
	color[0] = (thread->data->texturetab[pos] & 0xFF);
	color[1] = ((thread->data->texturetab[pos] & 0xFF00) >> 8);
	color[2] = ((thread->data->texturetab[pos] & 0xFF0000) >> 16);
	gradient = (double)DIST_VIEW
		/ (double)thread->ray.wall_size[thread->num % NBR_THREAD];
	color[0] -= gradient * color[0];
	color[1] -= gradient * color[1];
	color[2] -= gradient * color[2];
	thread->data->texturetab[pos] = (color[0] + (color[1] << 8)
		+ (color[2] << 16));
}

void			apply_textures(t_thread *thread, int type, int i, int ret)
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
	thread->ray.y_tex = (i * 64 - HEIGHT * 32 + thread->ray.height * 32)
		/ thread->ray.height;
	add_color_to_pixel_with_dist(thread, type, i, ret);
}
