/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 13:45:50 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/07 14:01:15 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	fill_map(t_wolf *data, int size, char *tmp, int i)
{
	int		actual_map;

	actual_map = 0;
	while (i < size)
	{
		if (i % data->map_width == 0 || i % data->map_width
			== data->map_width - 2)
			tmp[i++] = 'x';
		else if (i % data->map_width == data->map_width - 1)
		{
			tmp[i++] = '\n';
			if (data->map[actual_map])
				actual_map++;
		}
		else if (data->map[actual_map] && data->map[actual_map] != '\n')
			tmp[i++] = data->map[actual_map++];
		else
			tmp[i++] = 'x';
	}
	tmp[i] = 0;
}

void	*calcul_ray_by_thread(void *data)
{
	t_thread		*thread;

	thread = (t_thread*)data;
	while (thread->num < thread->data->win_width)
	{
		thread->ray.camx = 2 * thread->num
			/ (double)thread->data->win_width - 1;
		thread->ray.direction.x = thread->data->camera.direction.x
			+ thread->data->camera.plane.x * thread->ray.camx;
		thread->ray.direction.y = thread->data->camera.direction.y
			+ thread->data->camera.plane.y * thread->ray.camx;
		thread->ray.hit = 0;
		draw_pixel_column(thread);
		thread->num += NBR_THREAD;
	}
	pthread_exit(0);
}
