/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:41:44 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/08 12:45:44 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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
